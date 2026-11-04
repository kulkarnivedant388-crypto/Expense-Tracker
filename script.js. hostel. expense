let expenses = JSON.parse(localStorage.getItem('campus_expenses')) || [
    { amount: 120, category: 'Mess & Canteen', date: '2026-11-01', description: 'Hostel mess monthly advance portion' },
    { amount: 45, category: 'Stationery & Prints', date: '2026-11-02', description: 'Practical lab journal prints' }
];

let expenseChartInstance = null;

if(document.getElementById('date')) {
    document.getElementById('date').valueAsDate = new Date();
}

window.onload = function() {
    renderTable();
    updateMetrics();
    initChart();
};

function handleFormSubmit(e) {
    e.preventDefault();
    const amount = parseFloat(document.getElementById('amount').value);
    const category = document.getElementById('category').value;
    const date = document.getElementById('date').value;
    const description = document.getElementById('description').value;

    expenses.push({ amount, category, date, description });
    saveAndRefresh();
    document.getElementById('expenseForm').reset();
    document.getElementById('date').valueAsDate = new Date();
}

function deleteExpense(index) {
    expenses.splice(index, 1);
    saveAndRefresh();
}

function clearAllData() {
    if(confirm("Are you sure you want to clear all expense records?")) {
        expenses = [];
        saveAndRefresh();
    }
}

function saveAndRefresh() {
    localStorage.setItem('campus_expenses', JSON.stringify(expenses));
    renderTable();
    updateMetrics();
    updateChart();
}

function renderTable() {
    const tbody = document.getElementById('expenseTableBody');
    if(!tbody) return;
    tbody.innerHTML = '';
    if (expenses.length === 0) {
        tbody.innerHTML = `<tr><td colspan="5" class="p-6 text-center text-slate-400">No expenses recorded yet. Add your first item above!</td></tr>`;
        return;
    }
    expenses.forEach((exp, index) => {
        tbody.innerHTML += `
            <tr class="hover:bg-slate-50 transition">
                <td class="p-3 font-semibold text-slate-900">₹${exp.amount.toFixed(2)}</td>
                <td class="p-3"><span class="bg-indigo-50 text-indigo-700 px-2.5 py-1 rounded-full text-xs font-medium">${exp.category}</span></td>
                <td class="p-3 text-xs text-slate-500">${exp.date}</td>
                <td class="p-3 text-slate-700">${exp.description || '-'}</td>
                <td class="p-3 text-right">
                    <button onclick="deleteExpense(${index})" class="text-rose-500 hover:text-rose-700 p-1"><i class="fa-solid fa-trash-can"></i></button>
                </td>
            </tr>
        `;
    });
}

function updateMetrics() {
    const total = expenses.reduce((sum, exp) => sum + exp.amount, 0);
    const totalSpendEl = document.getElementById('totalSpend');
    const totalCountEl = document.getElementById('totalCount');
    const topCatEl = document.getElementById('topCategory');

    if(totalSpendEl) totalSpendEl.innerText = `₹${total.toFixed(2)}`;
    if(totalCountEl) totalCountEl.innerText = expenses.length;

    if (expenses.length > 0 && topCatEl) {
        const categoryCounts = {};
        expenses.forEach(e => categoryCounts[e.category] = (categoryCounts[e.category] || 0) + e.amount);
        const topCat = Object.keys(categoryCounts).reduce((a, b) => categoryCounts[a] > categoryCounts[b] ? a : b);
        topCatEl.innerText = topCat;
    } else if(topCatEl) {
        topCatEl.innerText = 'N/A';
    }
}

function initChart() {
    const canvas = document.getElementById('expenseChart');
    if(!canvas) return;
    const ctx = canvas.getContext('2d');
    expenseChartInstance = new Chart(ctx, {
        type: 'doughnut',
        data: getChartData(),
        options: {
            responsive: true,
            maintainAspectRatio: false,
            plugins: { legend: { position: 'right', labels: { boxWidth: 12, font: { size: 11 } } } }
        }
    });
}

function updateChart() {
    if(expenseChartInstance) {
        expenseChartInstance.data = getChartData();
        expenseChartInstance.update();
    }
}

function getChartData() {
    const categories = {};
    expenses.forEach(e => {
        categories[e.category] = (categories[e.category] || 0) + e.amount;
    });
    return {
        labels: Object.keys(categories),
        datasets: [{
            data: Object.values(categories),
            backgroundColor: ['#4f46e5', '#10b981', '#f59e0b', '#ef4444', '#8b5cf6', '#64748b'],
            borderWidth: 0
        }]
    };
}

function calculateSplit() {
    const total = parseFloat(document.getElementById('splitTotal').value);
    const count = parseInt(document.getElementById('splitCount').value);
    const resDiv = document.getElementById('splitResult');
    if(!total || !count || count <= 0) {
        alert("Please enter valid amount and number of people.");
        return;
    }
    const perPerson = total / count;
    resDiv.innerText = `Each person needs to pay: ₹${perPerson.toFixed(2)}`;
    resDiv.classList.remove('hidden');
}

function exportCSV() {
    let csvContent = "Amount,Category,Date,Description\n";
    expenses.forEach(e => {
        csvContent += `${e.amount},"${e.category}",${e.date},"${e.description}"\n`;
    });
    const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);
    const link = document.createElement("a");
    link.setAttribute("href", url);
    link.setAttribute("download", "expenses_data.csv");
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
}

function openCppModal() { document.getElementById('cppModal').classList.remove('hidden'); }
function closeCppModal() { document.getElementById('cppModal').classList.add('hidden'); }
