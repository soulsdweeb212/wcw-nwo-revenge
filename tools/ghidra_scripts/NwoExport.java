// Post-analysis: find functions in the given code ranges that nothing calls, then write the instruction listing,
// the function list and each function's decompiled C.
// Arguments: output dir, "start-end" hex range to export, then zero or more "start-end" hex ranges to sweep.
import java.io.PrintWriter;
import java.nio.file.*;
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;

public class NwoExport extends GhidraScript {
    private long lo(String r) { return Long.parseLong(r.split("-")[0], 16); }
    private long hi(String r) { return Long.parseLong(r.split("-")[1], 16); }

    // `addiu sp,sp,-N` on code nothing reached. Ghidra's own search does not know this compiler's prologues.
    private void sweep(long start, long end) throws Exception {
        Listing l = currentProgram.getListing();
        int found = 0;
        for (long p = start; p + 4 <= end; p += 4) {
            Address a = toAddr(p);
            if (l.getInstructionContaining(a) != null || l.getFunctionContaining(a) != null) continue;
            int w = getInt(a);
            if ((w & 0xFFFF8000) != 0x27BD8000) continue;
            disassemble(a);
            if (l.getInstructionAt(a) != null && createFunction(a, null) != null) found++;
        }
        println("sweep " + Long.toHexString(start) + ": " + found + " new functions");
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Path out = Paths.get(args[0]);
        long lo = lo(args[1]), hi = hi(args[1]);
        for (int i = 2; i < args.length; i++) sweep(lo(args[i]), hi(args[i]));
        Files.createDirectories(out.resolve("c"));
        Listing l = currentProgram.getListing();
        AddressSet range = new AddressSet(toAddr(lo), toAddr(hi - 1));

        try (PrintWriter w = new PrintWriter(Files.newBufferedWriter(out.resolve("instructions.tsv")))) {
            for (Instruction in : l.getInstructions(range, true)) {
                StringBuilder hex = new StringBuilder();
                for (byte b : in.getBytes()) hex.append(String.format("%02X", b));
                w.println(in.getAddress() + "\t" + hex + "\t" + in);
            }
        }
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        try (PrintWriter w = new PrintWriter(Files.newBufferedWriter(out.resolve("functions.tsv")))) {
            for (Function f : l.getFunctions(range, true)) {
                w.println(f.getEntryPoint() + "\t" + f.getBody().getNumAddresses() + "\t" + f.getName());
                DecompileResults r = d.decompileFunction(f, 120, monitor);
                String c = r.decompileCompleted() ? r.getDecompiledFunction().getC()
                                                  : "/* decompile failed: " + r.getErrorMessage() + " */\n";
                Files.writeString(out.resolve("c").resolve(f.getEntryPoint() + ".c"), c);
            }
        }
        d.dispose();
    }
}
