package Lab;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileIO {
	public static void main(String[] args) {
		String[] names = { "John", "Carl", "Ryan" };
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter("testOutput.txt"));
			
			writer.write("Writing to a file...");
			writer.write("\nwriting another line");
			for (String name : names) {
				writer.write("\n" + name);
			}
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		try {
			BufferedReader reader = new BufferedReader(new FileReader("testOutput.txt"));
			String line;
			while ((line = reader.readLine()) != null) {
				System.out.println(line);
			}
			reader.close();
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

};
