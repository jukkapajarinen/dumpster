window.onload = function() {

  // Adding items
  var form = document.getElementById("newitemform");
  form.onsubmit = function(e) {
    e.preventDefault();
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/todo", true);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send('item=' + document.getElementById("newitem").value);
    xhr.onreadystatechange = function() {window.location.reload()};
  };

  // Deleting items
  var items = document.getElementsByClassName("item");
  for(var i = 0; i < items.length ; i++) {
    items[i].addEventListener("click", function(e) {
      var xhr = new XMLHttpRequest();
      xhr.open("DELETE", "/todo/"+e.target.id, true);
      xhr.send();
      xhr.onreadystatechange = function() {window.location.reload()};
    });
  };


}
