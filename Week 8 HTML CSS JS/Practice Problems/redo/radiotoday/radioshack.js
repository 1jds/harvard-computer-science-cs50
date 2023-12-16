const rightSliders = document.querySelectorAll('.slide-in-from-right')

const fromRightOnScrollObserver = new IntersectionObserver(entries => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('appear-from-right')
        }
    })
})

rightSliders.forEach(rightSlider => {
    fromRightOnScrollObserver.observe(rightSlider)
})





const leftSliders = document.querySelectorAll('.slide-in-from-left')

const fromLeftOnScrollObserver = new IntersectionObserver(entries => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('appear-from-left')
        }
    })
})

leftSliders.forEach(leftSlider => {
    fromLeftOnScrollObserver.observe(leftSlider)
})




// This is how I had it before...
// const observer = new IntersectionObserver(entries => {
//     console.log(entries)
//     // Loop over the entries
//     entries.forEach(entry => {
//         // If the element is visible
//         if (entry.isIntersecting) {
//         // Add the animation class
//             entry.target.classList.add('our-story--decorative-circle-img-animation');
//         }
//     });
//     }
// );

// observer.observe(document.querySelector('.our-story--decorative-circle-img'));
