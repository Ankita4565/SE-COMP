import java.io.*;
import java.util.Arrays;
public class ExternalSort {
 public static void main(String[] args) throws IOException {
 int chunkSize = 1000; // Adjust the chunk size as per your memory constraints
 
 // Open input and output tapes
 BufferedReader input1 = new BufferedReader(new FileReader("input1.txt"));
 BufferedReader input2 = new BufferedReader(new FileReader("input2.txt"));
 BufferedWriter output1 = new BufferedWriter(new FileWriter("output1.txt"));
 BufferedWriter output2 = new BufferedWriter(new FileWriter("output2.txt"));
 // Read chunks of data, sort them, and write to output tapes
 String[] chunk1 = new String[chunkSize];
 String[] chunk2 = new String[chunkSize];
 int chunk1Size, chunk2Size;
 while ((chunk1Size = readChunk(input1, chunk1, chunkSize)) > 0 &&
 (chunk2Size = readChunk(input2, chunk2, chunkSize)) > 0) {
 Arrays.sort(chunk1, 0, chunk1Size);
 Arrays.sort(chunk2, 0, chunk2Size);
 writeChunk(output1, chunk1, chunk1Size);
 writeChunk(output2, chunk2, chunk2Size);
 }
 // Merge sorted chunks
 mergeSortedChunks(new BufferedReader(new FileReader("output1.txt")),
 new BufferedReader(new FileReader("output2.txt")),
 new BufferedWriter(new FileWriter("output_sorted.txt")));
 // Close input and output tapes
 input1.close();
 input2.close();
 output1.close();
 output2.close();
 }
 // Read a chunk of data from input tape
 private static int readChunk(BufferedReader reader, String[] chunk, int chunkSize) throws 
IOException {
 int i = 0;
 String line;
 while (i < chunkSize && (line = reader.readLine()) != null) {
 chunk[i++] = line;
 }
 return i;
 }
 // Write a chunk of data to output tape
 private static void writeChunk(BufferedWriter writer, String[] chunk, int size) throws 
IOException {
 for (int i = 0; i < size; i++) {
 writer.write(chunk[i]);
 writer.newLine();
 }
 }
 // Merge sorted chunks
 private static void mergeSortedChunks(BufferedReader reader1, BufferedReader reader2, 
BufferedWriter writer)
 throws IOException {
 String line1 = reader1.readLine();
 String line2 = reader2.readLine();
 while (line1 != null && line2 != null) {
 if (line1.compareTo(line2) <= 0) {
 writer.write(line1);
 writer.newLine();
 line1 = reader1.readLine();
 } else {
 writer.write(line2);
 writer.newLine();
 line2 = reader2.readLine();
 }
 }
 while (line1 != null) {
 writer.write(line1);
 writer.newLine();
 line1 = reader1.readLine();
 }
 while (line2 != null) {
 writer.write(line2);
 writer.newLine();
 line2 = reader2.readLine();
 }
 // Close readers and writer
 reader1.close();
 reader2.close();
 writer.close();
 }
}