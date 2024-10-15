
async function handleLogin(event) {
    event.preventDefault(); // Mencegah form dari pengiriman default

    const username = document.getElementById("username").value;
    const email = document.getElementById("email").value;
    const password = document.getElementById("password").value;

    const response = await fetch('/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, email, password })
    });

    const data = await response.json();
    if (data.success) {
        alert("Login berhasil! Token: " + data.token);
        // Redirect atau lakukan tindakan lain setelah login berhasil
    } else {
        alert(data.message || "Login gagal!");
    }
}