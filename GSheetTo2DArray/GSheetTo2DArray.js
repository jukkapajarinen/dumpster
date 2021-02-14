// GSheet area to 2-dimensional array
function GSheetTo2DArray(json, rowMin, rowMax, colMin, colMax) {
  var rowBounds = [rowMin, rowMax];
  var colBounds = [colMin, colMax];

  // Calculate data area height and width
  var height = rowBounds[1]-rowBounds[0]+1;
  var width = colBounds[1]-colBounds[0]+1;

  // Filter only desired data area
  allData = json.feed.entry;
  filteredData = [];
  allData.forEach(elem => {
    var row = parseInt(elem.gs$cell.row);
    var col = parseInt(elem.gs$cell.col);
    if(row >= rowBounds[0] && row <= rowBounds[1] && col >= colBounds[0] && col <= colBounds[1]) {
      // console.log(data[i].gs$cell);
      filteredData.push(elem.gs$cell);
    }
  });

  // Create 2-dimensional array of data
  cleanData = Array(height).fill(null).map(()=>Array(width).fill(null));
  filteredData.forEach(elem => cleanData[parseInt(elem.row)-rowBounds[0]][parseInt(elem.col)-colBounds[0]] = elem.$t);

  return cleanData;
}
