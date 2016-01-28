import java.sql.*;

class Sample
{
  public static void main (String args [])
       throws SQLException
  {
    // Load the Oracle JDBC driver
    DriverManager.registerDriver(new oracle.jdbc.OracleDriver());

    // Connect to the database
    Connection conn =
      DriverManager.getConnection ("jdbc:oracle:thin:@mmdb.inf.cs.cmu.edu:1521:mmdb", "MED14", "informedia");

    // Create a Statement
    Statement stmt = conn.createStatement ();

    // Select the MOVIE_NAME column from the MOVIE table
    ResultSet rset = stmt.executeQuery ("select MOVIE_NAME from MOVIE where MOVIE_ID=123");

    // Iterate through the result and print
    while (rset.next ())
      System.out.println (rset.getString (1));

    // Close the ResultSet
    rset.close();

    // Close the Statement
    stmt.close();

    // Close the connection
    conn.close();   
  }
}