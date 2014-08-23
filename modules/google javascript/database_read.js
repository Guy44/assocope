/**
 * 
 */
function foo() {
  var conn = Jdbc.getConnection("jdbc:mysql://:3306/", "user", "password");
  var stmt = conn.createStatement();
  stmt.setMaxRows(100);
  var start = new Date();
  var rs = stmt.executeQuery("select * from person");

  var doc = SpreadsheetApp.getActiveSpreadsheet();
  var cell = doc.getRange('a1');
  var row = 0;
  while(rs.next()) {
    cell.offset(row, 0).setValue(rs.getString(1));
    cell.offset(row, 1).setValue(rs.getString(2));
    cell.offset(row, 2).setValue(rs.getString(3));
    cell.offset(row, 3).setValue(rs.getString(4));
    row++;
  }
  rs.close();
  stmt.close();
  conn.close();
  var end = new Date();
  Logger.log("time took: " + (end.getTime() - start.getTime()));
}