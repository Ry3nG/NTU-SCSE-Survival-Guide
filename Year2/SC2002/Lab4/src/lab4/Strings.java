package lab4;

import java.util.Scanner;

public class Strings {
	public static void main(String[] args) {
		//callSelectionSort();
		callInsertionSort();
	}
	private static void callSelectionSort() {
		String[] strList; 
		int size;
		Scanner scan = new Scanner(System.in);
		System.out.print("\nHow many Strings do you want to sort? ");
		size = scan.nextInt();
		strList = new String[size];
		System.out.println("\nEnter the Strings...");
		for (int i = 0; i < size; i++)
			strList[i] = scan.next();
		Sorting.selectionSort(strList);
		System.out.println("\nYour Strings in sorted order...");
		for (int i = 0; i < size; i++)
			System.out.print(strList[i] + " ");
		System.out.println();
	}
	
	private static void callInsertionSort() {
		String[] strList; 
		int size;
		Scanner scan = new Scanner(System.in);
		System.out.print("\nHow many Strings do you want to sort? ");
		size = scan.nextInt();
		strList = new String[size];
		System.out.println("\nEnter the Strings...");
		for (int i = 0; i < size; i++)
			strList[i] = scan.next();
		Sorting.insertionSort(strList);
		System.out.println("\nYour Strings in sorted order...");
		for (int i = 0; i < size; i++)
			System.out.print(strList[i] + " ");
		System.out.println();
	}
}
