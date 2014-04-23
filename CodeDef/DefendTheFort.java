import java.io.*;
import java.util.*;
import java.io.Console;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
	
public final class DefendTheFort // changed class to final
{
	private static Scanner kb = null; // added global variables
	private static Scanner fileRead = null;
	private static Validater validater = null;
	private static PrintWriter printer = null;
	private static PrintWriter errorPrint = null;
	private static Console console = System.console();
	private final static int MAX_LOGIN = 5;
	
    public static void main(String[] args) throws NoSuchAlgorithmException
    {
			kb = new Scanner(System.in); //allocate scanner
			try{
				errorPrint = new PrintWriter("errorLog.txt"); // allocate error printer
			}catch( FileNotFoundException ne ){}
				
			validater = new Validater(); //allocate data validation object
			
			String firstName = getFirstName();
			String lastName = getLastName();
			
			String inputFile = getInputFile();		
			String outputFile = getOutputFile();
			
			long int1 = getFirstInteger();
			long int2 = getNextInteger();
			
			String securePassword = SetPass();
			validatePass( securePassword );
			/* 
			System.out.println("output file is: " + outputFile );
			System.out.println("input file is: " + inputFile );
			
			System.out.println("first number is: " + int1 );
			System.out.println("second number is: " + int2 );
			
			System.out.println("secure password is: " + securePassword ); */
			
			openInputFile( inputFile );
			openOutputFile( outputFile );
			try{
				printOutput( firstName, lastName, int1, int2 );
			}catch ( IOException ioe ) {
			errorPrint.write("\nError: "+ ioe.getMessage() );
			}finally{
				errorPrint.close();
				printer.close();
				kb.close();
				fileRead.close();
			}
				
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
        			errorPrint.write("\nError: "+ e.getMessage() );
        	   	}
        	}
        return name; 
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
        		errorPrint.write("\nError: "+ e.getMessage() );
        		}
        	}
        return name; 
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
        			errorPrint.write("\nError: "+ e.getMessage() );
        	   	}
        	}
        name += ".txt";
        
        return name; 
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
        		catch( NoSuchElementException ne ) {
        			errorPrint.write("\nError: "+ ne.getMessage() );
        	   	}
        	}
        name += ".txt";	
        return name; 
    }    
    
    private static long getFirstInteger()
    {          
    	long firstInt = 0;
    	boolean isValid = false;
    	
    	while ( !isValid )
    	{
    		try {
    			System.out.print("Please enter integer #1, ( -2^31 < X > 2^31 -1 ): ");
    			
    			if ( kb.hasNextInt() )
    				firstInt = kb.nextInt();    			
    			kb.nextLine();
    			
    			if ( firstInt != 0 )
    				isValid = validater.validateInt( firstInt );
    			System.out.println( "FIRST INT IS: " + firstInt );
    		}
    		catch ( NoSuchElementException ne ) {
    			errorPrint.write("\nError: "+ ne.getMessage() );
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
    			System.out.print("Please enter integer #2, ( -2^31 < X > 2^31 -1 ): ");
    			if ( kb.hasNextInt() )
    				secondInt = kb.nextInt();    			
    			kb.nextLine();
    			
    			if ( secondInt != 0 )
    				isValid = validater.validateInt( secondInt );
    		}
    		catch ( NoSuchElementException ne ) {
    			errorPrint.write("\nError: "+ ne.getMessage() );
    		}
    	}
    		return secondInt;
    }
    
    // sets the password and immediately encrypt it then delete the clear text from memory
    private static String SetPass() throws NoSuchAlgorithmException
    {
    	
    	String securePass = "";
    	
    	if ( console != null ) // System.console() returns null if launched from inside an 
    	{		// IDE such as Eclipse or Netbeans, works from within OS console
    		char[] pass = console.readPassword("Enter your password: ");
    		 
    		securePass = getSecurePassword( String.valueOf( pass ) );
    		Arrays.fill( pass, ' ');
    	}
    	else
    		System.out.println("Run this program from the OS console.");
    	return securePass;
    }
    
    // Encrypt the password using SHA-256
    private static String getSecurePassword( String passwordToHash )
	{
		String generatedPassword = null;
		try {                              
			MessageDigest md = MessageDigest.getInstance("SHA-256");
			
			byte[] bytes = md.digest(passwordToHash.getBytes());
			
			StringBuilder sb = new StringBuilder();
			                               
			for( int i=0; i< bytes.length; i++ )
				sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
			
			generatedPassword = sb.toString();
		} 
		catch (NoSuchAlgorithmException ne) 
		{
			errorPrint.write("\nError: "+ ne.getMessage() );
		}
		return generatedPassword;
	}
	
	private static void validatePass( String hashPass )
	{
		String authPass = "";
		int i = 0;
		
		while ( i < MAX_LOGIN )
		{
			char[] pass = console.readPassword("Re-Enter your password to authenticate (5 attempts): ");	
			authPass = getSecurePassword( String.valueOf( pass ) );
			Arrays.fill( pass, ' ');
			
			if ( validater.authenticate( authPass, hashPass ) )
			{
				System.out.println("Authentication successful!");
				return;
			}
			i++;
		}
		System.out.println("You have exhausted your login attempts, sorry.");
		return;
	}
	
	private static void openOutputFile( String outputFile )
	{
		try {
			printer = new PrintWriter( outputFile );			
		}
		catch ( FileNotFoundException fe ) {
			errorPrint.write("\nError: "+ fe.getMessage() );	
		}
	}
	
	private static void openInputFile( String inputFile )
	{
		try{
			fileRead = new Scanner(new FileReader( inputFile) );
		}
		catch ( FileNotFoundException fe ) {
			errorPrint.write("\nError: "+ fe.getMessage() );
		}
	}
	
	private static void printOutput( String Fname, String Lname, long int1, long int2 ) throws IOException
	{
		printer.write("First Name: \t"+ Fname + "\n" +
								"Last Name: \t"+ Lname + "\n" +
								int1 +" + "+ int2 +" = "+ (int1+int2) + "\n"+
								int1 +" * "+ int2 +" = "+ (int1*int2) +"\n\n");
		
		while ( fileRead.hasNextLine() )
			printer.write( fileRead.nextLine() +"\n" );					
	}
}
	
 
