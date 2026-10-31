// Pre-analysis: name the known functions and data, so Ghidra starts from what build.json already knows.
// Argument: a TSV of "func|data <TAB> hex address <TAB> name".
import java.nio.file.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;

public class NwoLabels extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (String line : Files.readAllLines(Paths.get(getScriptArgs()[0]))) {
            String[] f = line.split("\t");
            Address a = toAddr(Long.parseLong(f[1], 16));
            if (f[0].equals("func")) {
                disassemble(a);
                if (createFunction(a, f[2]) == null)
                    println("no function at " + a + " " + f[2]);
            } else {
                currentProgram.getSymbolTable().createLabel(a, f[2], SourceType.IMPORTED);
            }
        }
    }
}
