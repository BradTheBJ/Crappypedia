const input = document.getElementById('searchInput');
const button = document.getElementById('searchBtn');

button.addEventListener('click', () => {
    const query = input.value.trim();
    if (query) {
        window.location.href = `https://en.wikipedia.org/wiki/${encodeURIComponent(query)}`;
    }
});

// Allow pressing Enter key to trigger the search
input.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') {
        button.click();
    }
});
