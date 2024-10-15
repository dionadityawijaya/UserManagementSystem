async function handleRegister(event) {
    event.preventDefault(); // Mencegah form dari pengiriman default

    const username = document.getElementById("reg-username").value;
    const email = document.getElementById("reg-email").value;
    const password = document.getElementById("reg-password").value;

    const response = await fetch('/register', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, email, password })
    });

    const data = await response.json();
    if (data.success) {
        alert("Registrasi berhasil!");
        // Redirect atau lakukan tindakan lain setelah registrasi berhasil
    } else {
        alert(data.message || "Registrasi gagal!");
    }
}