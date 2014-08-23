/**
 * 
 */
function insert() {
  var conn = Jdbc.getConnection("jdbc:mysql://:/", "user", "password");
  conn.setAutoCommit(false);
  var stmt = conn.prepareStatement("insert into person (lname,fname) values (?,?)");
  var start = new Date();
  for (var i = 0; i < 5000; i++) {
    stmt.setObject(1, 'firstName' + i);
    stmt.setObject(2, 'lastName' + i);
    stmt.addBatch();
  }
  var res = stmt.executeBatch();
  conn.commit();
  conn.close();
  var endTime = new Date();
  Logger.log("time is " + (endTime.getTime() - start.getTime()) + "ms");
  Logger.log("res has " + res.length);
}