document.addEventListener("DOMContentLoaded", function () {
    const loginForm = document.getElementById("login-form");
    const errorMessage = document.getElementById("error-message");

    loginForm.addEventListener("submit", function (e) {
        e.preventDefault();
        const username = document.getElementById("username").value;
        const password = document.getElementById("password").value;

        if (username === "admin" && password === "admin") {
            errorMessage.textContent = "Login bem-sucedido!";
            location.href = 'section-one.html'
        } else {
            // Aqui você pode adicionar lógica para verificar o nome de usuário e senha.
            // Por enquanto, apenas exibimos uma mensagem de sucesso.
            errorMessage.textContent = "Não Possui cadastro";
        }
    });
});
