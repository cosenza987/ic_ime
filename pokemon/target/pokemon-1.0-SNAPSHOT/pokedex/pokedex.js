fetch("https://pokeapi.co/api/v2/pokemon?limit=100000&offset=0").then(
  res => {
    res.json().then(
      data => {
        if (data.results.length > 0) {

          var tem = "";
          var count = 0;
          var list = [];
          data.results.forEach((itemData) => {
            list.push(fetch(itemData.url));
          });
          Promise.all(list).then(
            ret => {
            console.log(ret);
            ret.forEach((poke) =>{
                poke.json().then(pkm => {
                    var temp = "";
                    var total = 0;
                    count += 1;
                    temp += "<tr>";
                    temp += "<td class=\"cell-num\" data-sort-value=\"1\"><picture class=\"infocard-cell-img\"><source srcset="+ pkm.sprites.front_default +" width=\"60\" height=\"56\" type=\"image/png\"><img class=\"img-fixed icon-pkmn\" src="+ pkm.sprites.front_default +" width=\"60\" height=\"56\" loading=\"lazy\"></picture><span class=\"infocard-cell-data\"> #" + ("000" + count).slice(-4) + "</span></td>";
                    temp += "<td class=\"cell-name\"><a class=\"ent-name\" href=\"../pokedex/pokemon/pokemon.html?&pokemon=" + pkm.name + "\" title=\"View Pokedex for #" + ("000" + count).slice(-4) + " " + pkm.name +"\">" + pkm.name + "</a></td>";
                    temp += "<td class=\"cell-icon\">";
                    pkm.types.forEach((t) => {
                        temp += "<a class=\"type-icon type-" + t.type.name + "\">" + t.type.name + "</a><br>"; 
                    })
                    temp += "</td>";
                    pkm.stats.forEach((stat) => {
                        temp += "<td class=\"cell-num\">" + stat.base_stat + "</td>";
                        total += stat.base_stat;
                    })
                    temp += "<td class=\"cell-num cell-total\">" + total + "</td></tr>";
                    tem += temp;
                    if(count == 1302){
                        document.getElementById('pokedex_data').innerHTML = tem;
                    }
                })
                }
            )
        }
          )
        }
      }
    )
  }
)

//filter

function name_filter() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("filter-pkmn-name");
  filter = input.value.toUpperCase();
  console.log(filter);
  table = document.getElementById("pokedex");
  tableBody = table.getElementsByTagName("tbody")[0];
  tr = tableBody.getElementsByTagName("tr");
  console.log(tableBody)
  // Loop through all table rows, and hide those who don't match the search query
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[1];
    if (td) {
      txtValue = td.textContent || td.innerText;
      console.log(txtValue);
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }
  }
}

function type_filter() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("filter-pkmn-type");
  filter = input.value.toUpperCase();
  table = document.getElementById("pokedex");
  tableBody = table.getElementsByTagName("tbody")[0];
  tr = tableBody.getElementsByTagName("tr");

  // Loop through all table rows, and hide those who don't match the search query
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[2];
    if (td) {
      types = td.getElementsByTagName("a");
      for (j = 0; j < types.length; j++) {
        txtValue = types[j].textContent || types[j].innerText;
        if (txtValue.toUpperCase().indexOf(filter) > -1) {
          if(tr[i].style.display == "") tr[i].style.display = ""; break;
        } else {
          tr[i].style.display = "none";
        }
      }
    }
  }
}

function filter(){
  console.log("called filter");
  name_filter();
  console.log("called name, calling type");
  type_filter();
}

//sort

const getCellValue = (tr, idx) => tr.children[idx].innerText || tr.children[idx].textContent;

const comparer = (idx, asc) => (a, b) => ((v1, v2) => 
    v1 !== '' && v2 !== '' && !isNaN(v1) && !isNaN(v2) ? v1 - v2 : v1.toString().localeCompare(v2)
    )(getCellValue(asc ? a : b, idx), getCellValue(asc ? b : a, idx));


document.querySelectorAll('th').forEach(th => {if(th.classList[0] == "sorting"){th.addEventListener('click', (() => {
  const table = th.closest('table');
  const tbody = table.querySelector('tbody');
  if(th.getAttribute("asc") == "false"){
    console.log(th.attributes[1]);
    th.setAttribute("asc","true");
    console.log(th.attributes[1]);
    Array.from(tbody.querySelectorAll('tr'))
    .sort(comparer(Array.from(th.parentNode.children).indexOf(th), false))
    .forEach(tr => tbody.appendChild(tr) );
  }
  else{
    console.log(th.attributes[1]);
    th.setAttribute("asc","false");
    console.log(th.attributes[1]);
    Array.from(tbody.querySelectorAll('tr'))
    .sort(comparer(Array.from(th.parentNode.children).indexOf(th), true))
    .forEach(tr => tbody.appendChild(tr));
  }

}))}});

// check user logged in

function checkUser(){
  document.getElementById("profile").innerHTML = "<a href=\"../login/login.html\"> Login </a>"
    $.get('${pageContext.request.contextPath}/myservlet', function(data) {
        if(data == null){
          document.getElementById("profile").innerHTML = "<a href=\"../login/login.html\"> Login </a>";
        }
        else{
          document.getElementById("profile").innerHTML = "<a href=\"../Profile/?&user=" + data.username + "\">" + data.username + "</a>";
        }
    });
}