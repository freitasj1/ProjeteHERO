document.addEventListener("DOMContentLoaded", function () {
    const loginForm = document.getElementById("login-form");
    const errorMessage = document.getElementById("error-message");

   
    const users = [
        { username: "admin", password: "admin" },
        { username: "Pinguim", password: "PoloNorte" },
        { username: "FrangoFrito", password: "Senha" },
        { username: "BobEsponja", password: "LulaMolusco" },


    
    ];

    loginForm.addEventListener("submit", function (e) {
        e.preventDefault();
        const username = document.getElementById("username").value;
        const password = document.getElementById("password").value;

       
        const user = users.find(user => user.username === username && user.password === password);

        if (user) {
            errorMessage.textContent = "Login bem-sucedido!";
            location.href = 'section-one.html';
        } else {
            errorMessage.textContent = "Credenciais inválidas";
        }
    });
});

