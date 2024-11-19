//Riyasat Rashid
//4-28-24


import java.io.*;

public class Project4348 {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java Project4348 <process_type>");
            System.err.println("process_type: parent | child1 | child2");
            System.exit(1);
        }

        String processType = args[0];

        if (processType.equals("parent")) {
            parentProcess();
        } else if (processType.equals("child1")) {
            childProcess("d1/f1", "d1/f2");
        } else if (processType.equals("child2")) {
            childProcess("d2/f3", "d2/f4");
        } else {
            System.err.println("Invalid process type: " + processType);
            System.exit(1);
        }
    }

    private static void parentProcess() {
        try {
            ProcessBuilder pb1 = new ProcessBuilder("java", "Project4348", "child1");
            ProcessBuilder pb2 = new ProcessBuilder("java", "Project4348", "child2");

            Process child1 = pb1.start();
            Process child2 = pb2.start();

            OutputStream child1Out = child1.getOutputStream();
            OutputStream child2Out = child2.getOutputStream();

            sendFileContentsToProcess("d0/f1", child1Out);
            sendFileContentsToProcess("d0/f2", child1Out);
            sendFileContentsToProcess("d0/f3", child2Out);
            sendFileContentsToProcess("d0/f4", child2Out);

            child1Out.close();
            child2Out.close();

            child1.waitFor();
            child2.waitFor();

            System.out.println("Parent process finished.");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void sendFileContentsToProcess(String fileName, OutputStream processOut) throws IOException {
        BufferedReader fileReader = new BufferedReader(new FileReader(fileName));
        PrintWriter processWriter = new PrintWriter(processOut);
        String line;
        while ((line = fileReader.readLine()) != null) {
            processWriter.println(line);
        }
        processWriter.flush();
        fileReader.close();
    }

    private static void childProcess(String outputFile1, String outputFile2) {
        try {
            PrintWriter out1 = new PrintWriter(new FileWriter(outputFile1));
            PrintWriter out2 = new PrintWriter(new FileWriter(outputFile2));

            BufferedReader processIn = new BufferedReader(new InputStreamReader(System.in));
            String line;
            while ((line = processIn.readLine()) != null) {
                out1.println(line);
                out2.println(line);
            }

            out1.close();
            out2.close();
            processIn.close();

            System.out.println("Child process finished.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}