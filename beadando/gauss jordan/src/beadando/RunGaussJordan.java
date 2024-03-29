package beadando;

import java.io.IOException;
import java.io.PrintWriter;

public class RunGaussJordan {

	public static void main(String[] args) {
		
		        int matrixLenght = 1000; 
		        double[][] matrix = createRandomMatrix(matrixLenght);
		        long startTime;
		        long endTime;
		        long totalTime;
		        long totalTimeParallel;
		        int maxNumThreads = 1003;
		        GaussJordan gaussjordan = new GaussJordan(matrix);
		        
		        startTime = System.currentTimeMillis(); 
		        
		        gaussjordan.gaussJordanElimination(0,matrixLenght);
		        
		        endTime = System.currentTimeMillis(); 
		        totalTime = endTime - startTime; 
		        
		        System.out.println("Futtatási idő(szekvenciális): " + totalTime + " ms"); 
		        
		         
		        try {
		            PrintWriter writer = new PrintWriter("results.txt", "UTF-8");

		            writer.println(totalTime);
			    
			        for(int i = 2;i<maxNumThreads;i+=100) {
			        	matrix = createRandomMatrix(matrixLenght);
			        
			        	startTime = System.currentTimeMillis();
			        
			        	GaussJordanParallel.gaussJordanEliminationParallel(matrix, i); 
			        
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


