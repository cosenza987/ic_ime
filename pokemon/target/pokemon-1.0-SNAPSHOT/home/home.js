function checkUser(){
    document.getElementById("profile").innerHTML = "<a href=\"../login/login.html\"> Login </a>"
      $.get('${pageContext.request.contextPath}/servlet', function(data) {
          if(data == null){
            document.getElementById("profile").innerHTML = "<a href=\"../login/login.html\"> Login </a>";
          }
          else{
            document.getElementById("profile").innerHTML = "<a href=\"../Profile/?&user=" + data.username + "\">" + data.username + "</a>";
          }
      });
  }