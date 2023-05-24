package beadando;

import java.io.IOException;
import java.io.PrintWriter;

public class RunGaussJordan {

	public static void main(String[] args) {
		        int n = 1000; 
		        double[][] matrix = createRandomMatrix(n);
		        long startTime;
		        long endTime;
		        long totalTime;
		        long totalTimeParallel = 0;
		        
		        
		        startTime = System.currentTimeMillis(); 
		        matrix = createRandomMatrix(n);
		        GaussJordan.gaussJordanElimination(matrix); 
		        endTime = System.currentTimeMillis(); 
		        totalTime = endTime - startTime; 
		        System.out.println("Futtatási idő(szekvenciális): " + totalTime + " ms"); 
		        
		         
		        try {
		            PrintWriter writer = new PrintWriter("results.txt", "UTF-8");

			        writer.println(totalTime);
		        for(int i = 2;i<1003;i+=100) {
		        startTime = System.currentTimeMillis();
		        GaussJordanParallel.gaussJordanElimination(matrix, i); 
		        endTime = System.currentTimeMillis(); 
		        totalTimeParallel = endTime - startTime; 
		        System.out.println("Futtatási idő(párhuzamos " + i + " szálon): " + totalTimeParallel + " ms");
		        if(totalTime > totalTimeParallel) {
		        System.out.println("A párhuzamos eset " + (totalTime - totalTimeParallel) + " ms-el gyorsabb volt");
		        }
		        else {
			        System.out.println("A szekvenciális eset " + (totalTimeParallel - totalTime) + " ms-el gyorsabb volt");
		        }
		        writer.print(i);
		        writer.print(" ");
		        writer.println(totalTimeParallel);

		        }
		        
		        
		            
		            writer.close();
		            
		        } catch (IOException e) {
		            System.out.println("Hiba történt a fájl írása során.");
		        }
		    }

		    
		    private static double[][] createRandomMatrix(int n) {
		        double[][] matrix = new double[n][n];
		        for (int i = 0; i < n; i++) {
		            for (int j = 0; j < n; j++) {
		                matrix[i][j] = Math.random();
		            }
		        }
		        return matrix;
		    }
	}


