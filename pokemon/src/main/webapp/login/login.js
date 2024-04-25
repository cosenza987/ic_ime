document.addEventListener('DOMContentLoaded', () => {
    document.querySelector("#login").addEventListener('submit', async e => {
        e.preventDefault();
        let form = document.forms.login;
        const formData = new FormData(form);
        const data = {
            username: formData.get('usernameLogin'),
            password: formData.get('passwordLogin')
        };
        const searchParams = new URLSearchParams(data);
        const response = await fetch('/pokemon_war_exploded/servlet2', {
            method: 'POST',
            body: searchParams
        });
        if (response.ok) {
            const { token } = await response.json();
            localStorage.setItem('token', token);
            window.location.href = '/pokemon_war_exploded/home/home.html';
        } else {
            const error = await response.json();
            alert(error.message);
        }
    });
    document.querySelector("#register").addEventListener('submit', async e => {
        e.preventDefault();
        let form = document.forms.register;
        const formData = new FormData(form);
        const data = {
            username: formData.get('usernameRegister'),
            email: formData.get('emailRegister'),
            password: formData.get('passwordRegister')
        };
        const searchParams = new URLSearchParams(data);
        //console.log(searchParams.toString());
        const response = await fetch('/pokemon_war_exploded/servlet', {
            method: 'POST',
            body: searchParams
        });
        console.log(data);
        console.log(JSON.stringify(data));
        if (response.ok) {
            const { token } = await response.json();
            localStorage.setItem('token', token);
            window.location.href = '/pokemon_war_exploded/home/home.html';
        } else {
            const error = await response.json();
            alert(error.message);
        }
    });
});


// password and username checking

function checkUser()
{
    var user = document.getElementById('username');
    var message = document.getElementById('error-nwl');
    var goodColor = "#66cc66";
    var badColor = "#ff6666";
 	
    if(user.value.length > 3)
    {
        user.style.backgroundColor = goodColor;
        message.style.color = goodColor;
        message.innerHTML = "character number ok!"
    }
    else
    {
        user.style.backgroundColor = badColor;
        message.style.color = badColor;
        message.innerHTML = "your username must have at least 4 digit!"
        return;
    }
}  

function checkPass()
{
    var pass = document.getElementById('password');
    var message = document.getElementById('error-nwl');
    var goodColor = "#66cc66";
    var badColor = "#ff6666";
 	
    if(pass.value.length > 5)
    {
        pass.style.backgroundColor = goodColor;
        message.style.color = goodColor;
        message.innerHTML = "character number ok!"
    }
    else
    {
        pass.style.backgroundColor = badColor;
        message.style.color = badColor;
        message.innerHTML = " your username must have at least 6 digit!"
        return;
    }
}  