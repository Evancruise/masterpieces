const balance = document.getElementById("balance");
const inflow = document.getElementById("income");
const outflow = document.getElementById("expense");
const list = document.getElementById("list");
const form = document.getElementById("form");
//const form2 = document.getElementById("form2");
const text = document.getElementById("text");
const amount = document.getElementById("amount");

// var excelIO = new GC.Spread.Excel.IO();

// Get transactions from local storage
const localStorageTransactions = JSON.parse(localStorage.getItem("transactions"));

let transactions = localStorage.getItem("transactions") !== null ? localStorageTransactions : [];

// Add transaction function
function addTransaction(e) {
    e.preventDefault();
    console.log('button triggered!!');

    // Check if the fields are empty or not
    if (text.value.trim() === "" || amount.value.trim() === "") {
        document.getElementById("error_msg").innerHTML = "<span> Error. Enter text and amount first. </span>";
        setTimeout (
            () => (document.getElementById("error_msg").innerHTML = ""),
            5000
        );
    } else {
        const transaction = {
            id: generateID(), 
            text: text.value,
            amount: +amount.value,
        };

        transactions.push(transaction);

        // add transaction to document object model DOM for local storage
        addTransactionDOM(transaction);

        // invoke addTransaction DOM
        updateValues();

        updateLocalStorage();

        text.value = "";
        amount.text = "";
    }
}

// Generate random ID for the delete button
function generateID() {
    return Math.floor(Math.random() * 100000000);
}


// Transaction history
function addTransactionDOM(transaction) {
    const sign = transaction.amount < 0 ? "-" : "+";
    const item = document.createElement("li");
    item.classList.add(transaction.amount < 0 ? "minus" : "plus");
    
    // Adding (rendering) the list element with the delete button on the page using innerHTML property
    item.innerHTML = ` ${transaction.text}      ${sign} ${Math.abs(transaction.amount)}
    <button class="delete-btn" onclick="removeTransaction(${transaction.id})"> X </botton>`;
    // console.log(list);
    list.appendChild(item);
}

// Update the balance

function updateValues() {
    const amounts = transactions.map((transaction) => transaction.amount);
    
    const total = amounts.reduce((bal, value) => (bal += value), 0);
    
    const income = amounts.filter((value) => value > 0).reduce((bal, value) => (bal += value), 0);
    
    const expense = amounts.filter((value) => value < 0).reduce((bal, value) => (bal += value), 0 * -(1));

    // displaying balance
    balance.innerText = `$${total}`;
    inflow.innerText = `$${income}`;
    outflow.innerText = `$${expense}`;
}

// Remove transaction by id
function removeTransaction(id) {
    transactions = transactions.filter((transaction) => transaction.id !== id);

    // need to update the storage after removing
    updateLocalStorage();
    
    // need to start the whole app
    start();
}

// update local storage
function updateLocalStorage() {
    localStorage.setItem("transactions", JSON.stringify(transactions));
}

function start() {
    list.innerHTML = "";
    transactions.forEach(addTransactionDOM);
    updateValues();
}


function transactions_export_excel(e) {
    e.preventDefault();
    
    console.log('export button triggered!!');
    // console.log(e);

    const checkList = JSON.parse(localStorage.getItem("transactions"));

    console.log(checkList);

    const createCSV = require('csv-writer').createObjectCsvWriter;

    const csv = createCSV({
        path: "account.csv",
        header: [
            {id: "ani", title: "ANIMAL"},
            {id: "desc", title: "DESCRIPTION"}
        ]
    });

    csv.writeRecords([
        { ani: "Doge", desc: "Goodest Boy" },
        { ani: "Cate", desc: "Evil" },
        { ani: "Birb", desc: "Happy Wings" }
    ]).then(() => { console.log("Done!"); });

    //  var table1 = document.querySelector("#table1");
    // let ws = window.XLSX.utils.json_to_sheet(transactions)
    // console.log(ws);

    //excelIO.save(checkList, function (blob) {  
    //    saveAs(blob, 'pricelist.xlsx');  
    //}, function (e) {  
    //    if (e.errorCode === 1) {  
    //        alert(e.errorMessage);  
    //    }  
    //});


    // workbook = new GC.Spread.Sheets.Workbook(checkList);

    // console.log(workbook);

    //let wb = XLSX.utils.book_new()

    //XLSX.utils.book_append_sheet(wb, ws, 'sheet')
    //let wb_out = XLSX.write(wb, {bookType: 'xlsx', type: 'array'})
    //let _blob = new Blob([wb_out], {type: 'application/octet-stream'})
    //FileSaver(_blob, 'account_history.xlsx')

    // var sheet = XLSX.utils.table_to_sheet(table);
    // openDownloadDialog(sheet2blob(sheet),'下载.xlsx');
}


start();
console.log('start~');
form.addEventListener("submit", addTransaction, false)
//form2.addEventListener("click", transactions_export_excel, false)