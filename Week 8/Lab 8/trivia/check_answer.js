// this ensures the code runs only when the page is fully loaded for the user.
document.addEventListener('DOMContentLoaded', function() {

    // assigns the button with the class .correct to correct, and if it is clicked, its bg-color is
    // set to green and "Correct!" appears below the options.
    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function() {
        correct.style.backgroundColor = 'green';
        document.querySelector('#feedback1').innerHTML = 'Correct!';
    });

    // assigns the buttons with the class .incorrect to wrong_answers, which is an array, and if they
    // are clicked, its bg-color is set to red and "Incorrect" appears below the options.
    let wrong_answers = document.querySelectorAll('.incorrect');
    for (let i = 0; i < wrong_answers.length; i++){
        wrong_answers[i].addEventListener('click', function() {
            wrong_answers[i].style.backgroundColor = 'red';
            document.querySelector('#feedback1').innerHTML = 'Incorrect';
        });
    }
    // If the Check Answer button is pressed, the value of the input text box is checked. If it is correct
    // bg-color is set to green and "Correct!" appears below the text box. Else, its bg-color is set to red
    // & the "Incorrect" appears below the text box.
    document.querySelector('#check').addEventListener('click', function(){
        let input = document.querySelector('input');
        if (input.value == 'Mercedes'){
            input.style.backgroundColor = 'green';
            document.querySelector('#feedback2').innerHTML = 'Correct!';
        }

        else {
            input.style.backgroundColor = 'red';
            document.querySelector('#feedback2').innerHTML = 'Incorrect';
        }
    });

});