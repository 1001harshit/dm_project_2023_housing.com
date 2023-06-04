function openFilterWindow() {
    var filterWindow = document.getElementById("filterWindow");
    filterWindow.style.display = "block";
  }
  
  function applyFilter() {
    var selectedOption = document.getElementById("mySelect").value;
    
    var items = document.getElementsByClassName("item");
    
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      if (selectedOption === "all" || item.classList.contains(selectedOption)) {
        item.style.display = "block";
      } else {
        item.style.display = "none";
      }
    }
    
    var filterWindow = document.getElementById("filterWindow");
    filterWindow.style.display = "none";
  }
  
  const closeButton = document.querySelector('.close-button');
  const windowElement = document.querySelector('.window');
  
  closeButton.addEventListener('click', function() {
    windowElement.style.display = 'none';
  });
  