import java.util.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.lang.Integer;

public final class Validater
{
	private final static int MAX_BUF = 50; 
	private final static Pattern regx = Pattern.compile("^[a-zA-Z0-9]+$");
	
	public Validater()	{}
	
	protected boolean validateString( String name )
	{
		String input =  name;
		Matcher match = regx.matcher(input);
        				
   		if ( match.matches() && input.length() < MAX_BUF )
   			return true;
   		
   		return false;	
	}
	protected boolean validateInt( long number )
	{
		long n = number;
			
		if ( n <= Integer.MAX_VALUE && n >= Integer.MIN_VALUE )
			return true;
		
		return false;		
	}	
}
