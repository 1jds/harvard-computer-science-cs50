const options = {
    root: null,
    rootMargin: '0px',
    threshold: 0.1
}

const scrollObserver = new IntersectionObserver(entries => {
    entries.forEach((entry, index) => {
        if (entry.isIntersecting && entry.target.classList.contains('slide-in-from-right')) {
            entry.target.classList.add('appear-from-right')
        }
        else if (entry.isIntersecting && entry.target.classList.contains('slide-in-from-left')) {
            entry.target.classList.add('appear-from-left')
        }
        else if (entry.isIntersecting && entry.target.classList.contains('will-fade-in')) {
            entry.target.classList.add('fade-in')
        }
        else if (entry.isIntersecting && entry.target.classList.contains('will-slide-up')) {
            entry.target.classList.add('slide-up')
        }
    })
}, options)

const itemsToAnimate = document.querySelectorAll('.slide-in-from-right, .slide-in-from-left, .will-fade-in, .will-slide-up').forEach(item => {
    scrollObserver.observe(item)
})



