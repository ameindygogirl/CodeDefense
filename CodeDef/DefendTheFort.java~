import java.io.*;
import java.util.*;
	
public final class DefendTheFort // changed class to final
{
	private static Scanner kb = null;		// added global variables
	private static Validater validater = null;
	
    public static void main(String[] args)
    {
			kb = new Scanner(System.in); //allocate scanner
			
			validater = new Validater();
			
			String inputFile = "";
			String outputFile = "";
			String firstName= "";
			String lastName = "";
			long int1, int2;
			
			firstName = getFirstName();
			lastName = getLastName();
			
			inputFile = getInputFile();		
			outputFile = getOutputFile();
			
			int1 = getFirstInteger();
			int2 = getNextInteger();
			
			System.out.println("output file is: " + outputFile );
			System.out.println("input file is: " + inputFile );
			
			System.out.println("first number is: " + int1 );
			System.out.println("second number is: " + int2 );
	 }
	 
	 private static String getFirstName()
	 {
	 	 String name = ""; 
        boolean isValid = false;
        	// asking user for only the name of the file without extension and adding ".txt" 
        	// if input is validated
        while ( !isValid )
        	{
        		try{
        				System.out.print("Please enter your first name (50 chars): ");
        				name = kb.nextLine();
        				isValid = validater.validateString( name );
        		}
        		catch( NoSuchElementException e ) {
        			System.err.println("\nError: "+ e.getMessage() );
        			e.printStackTrace();	//remove printstacktrace later
        			System.exit(1);
        	   	}
        	}
        return name; //change method return type to void and instead call a method that
        						//will create the file.
	 }
	 
	 private static String getLastName()
	 {
	 	 String name = ""; 
	 	 boolean isValid = false;
        	// asking user for only the name of the file without extension and adding ".txt" 
        	// if input is validated
        while ( !isValid )
        {
        	try	{
        				System.out.print("Please enter your last name (50 chars): ");
        				name = kb.nextLine();
        				isValid = validater.validateString( name );
        		}
        	catch( NoSuchElementException e ) {
        		System.err.println("\nError: "+ e.getMessage() );
        		e.printStackTrace();	//remove printstacktrace later
        		System.exit(1);
        		}
        	}
        	return name; //change method return type to void and instead call a method that
        						//will print the name to a file
	 }

    private static String getOutputFile()
    {
        String name = ""; 
        boolean isValid = false;
        	// asking user for only the name of the file without extension and adding ".txt" 
        	// if input is validated
        while ( !isValid )
        	{
        		try{
        				System.out.print("Please enter the output file name WITHOUT extension(50 chars): ");
        				name = kb.nextLine();
        				isValid = validater.validateString( name );
        		}
        		catch( NoSuchElementException e ) {
        			System.err.println("\nError: "+ e.getMessage() );
        			e.printStackTrace();	//remove printstacktrace later
        			System.exit(1);
        	   	}
        	}
        name += ".txt";	
        return name; //change method return type to void and instead call a method that
        						//will print the name to a file
    }
    
    private static String getInputFile()
    {
        String name = ""; 
        boolean isValid = false;
        	// asking user for only the name of the file without extension and adding ".txt" 
        	// if input is validated
        while ( !isValid )
        	{
        		try{
        				System.out.print("Please enter the input file name WITHOUT extension (50 chars): ");
        				name = kb.nextLine();
        				isValid = validater.validateString( name );
        		}
        		catch( NoSuchElementException e ) {
        			System.err.println("\nError: "+ e.getMessage() );
        			e.printStackTrace();	//remove printstacktrace later
        			System.exit(1);
        	   	}
        	}
        name += ".txt";	
        return name; //change method return type to void and instead call a method that
        						//will create the file.
    }    
    
    private static long getFirstInteger()
    {
    	long firstInt = 0;
    	boolean isValid = false;
    	
    	while ( !isValid )
    	{
    		try {
    			System.out.print("Please integer #1, ( -2^31 < X > 2^31 -1 ): ");
    			firstInt = kb.nextInt();    			
    			kb.nextLine();
    			
    			isValid = validater.validateInt( firstInt );
    		}
    		catch ( NoSuchElementException e ) {
    			System.err.println("\nError: "+ e.getMessage() );
    			e.printStackTrace();
    			System.exit(1);
    		}
    	}
    	return firstInt;
    }
    
    private static long getNextInteger()
    {
    	long secondInt = 0;
    	boolean isValid = false;
    	
    	while ( !isValid )
    	{
    		try {
    			System.out.print("Please integer #2, ( -2^31 < X > 2^31 -1 ): ");
    			if ( kb.hasNext() )
    				secondInt = kb.nextInt();    			
    			kb.nextLine();
    			
    			isValid = validater.validateInt( secondInt );
    		}
    		catch ( NoSuchElementException e ) {
    			System.err.println("\nError: "+ e.getMessage() );
    			e.printStackTrace();
    			System.exit(1);
    		}
    	}
    		return secondInt;
    }
}
	
 
