 //DOM Elements
 const circles = document.querySelectorAll(".circle"),
 progressBar = document.querySelector(".indicator"),
 buttons = document.querySelectorAll("button");

let currentStep = 1;

// function that updates the current step and updates the DOM
const updateSteps = (e) => {
 // update current step based on the button clicked
 currentStep = e.target.id === "next" ? ++currentStep : --currentStep;

 // loop through all circles and add/remove "active" class based on their index and current step
 circles.forEach((circle, index) => {
   circle.classList[`${index < currentStep ? "add" : "remove"}`]("active");
 });

 // update progress bar width based on current step
 progressBar.style.width = `${((currentStep - 1) / (circles.length - 1)) * 100}%`;

 // check if current step is last step or first step and disable corresponding buttons
 if (currentStep === circles.length) {
   buttons[1].disabled = true;
 } else if (currentStep === 1) {
   buttons[0].disabled = true;
 } else {
   buttons.forEach((button) => (button.disabled = false));
 }
};



function redirecionar1() {
   location.href = "https://www.tinkercad.com/joinclass/ED4HKXZUJ";
}



    function sub(){
        var name = document.getElementById("name").value;
        var phone = document.getElementById("phone").value
        var email = document.getElementById("email").value
        var message = document.getElementById("message").value
        if(name != "" && phone != "" && email != "" && message != ""){
          errorMessage.textContent = "Login bem-sucedido!";
        } else {
          errorMessage.textContent = "Credenciais inválidas";
      }
        
    }