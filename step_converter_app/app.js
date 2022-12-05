
document.querySelector(".calculate").addEventListener("click", function(){
    document.getElementById("km").style.display = "none";
    document.getElementById("calories").style.display = "none";
    document.querySelector(".loader").style.display = "block";
    setTimeout(steps_conv, 2000);
})

document.querySelector(".clear").addEventListener("click", clear)

function steps_conv() {
    const steps = document.getElementById('steps').value;
    let index = (steps * 0.0008045).toFixed(2);
    let index1 = (index * 55).toFixed(2);
    console.log("Your steps in KM:" + steps)
    if (steps != 0) {
        const km = document.getElementById("km");
        const calories = document.getElementById("calories");

        km.innerHTML = "KM walked = " + index + "Km";
        calories.innerHTML = "Calories burned = " + index1 + "Cal";

        document.getElementById("km").style.display = "block";
        document.getElementById("calories").style.display = "block";
        document.querySelector(".loader").style.display = "none";
    } else {
        error()
        function error() {
            document.getElementById("km").style.display = "block";
            document.getElementById("calories").style.display = "block";
            document.querySelector(".loader").style.display = "none";

            document.getElementById("km").innerHTML = "<span style='color:black; background-color:pink, border-radius=10px, padding:3px;'> Error: Enter Number of steps first!"

            setTimeout(() => {
                document.getElementById("km").innerHTML = "";
                document.getElementById("calories").innerHTML = "";
            }, 5000);
        }
    }
}


function clear() {
    document.getElementById("km").value = "";
    document.getElementById("calories").value = "";
    document.getElementById("steps").value = "";
}