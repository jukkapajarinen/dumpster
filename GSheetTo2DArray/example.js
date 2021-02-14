// Declare GSheet specific variables
var gSheetID = "asdf";
var rowMin = 1;
var rowMax = 10;
var colMin = 1;
var colMax = 10;

// Fetch data from GSheets
$.getJSON("https://spreadsheets.google.com/feeds/cells/"+sheetID+"/1/public/full?alt=json", function(json){
  var data = GSheetTo2DArray(json, rowMin, rowMax, colMin, colMax);
  var html = "<tbody>";
  for (var i = 0 ; i < data.length ; i++) {
    html += "<tr>";
    for (var j = 0 ; j < data[i].length ; j++) {
      if(i == 0) {
        html += "<th>"+data[i][j]+"</th>";
      } else {
        html += "<td>"+data[i][j]+"</td>";
      }
    }
    html += "</tr>";
  }
  html += "</tbody>";
  $('table#myTable').html(html);
}).fail(function () {
  $('table#myTable').replaceWith('<p>Error while reading data.</p>');
});