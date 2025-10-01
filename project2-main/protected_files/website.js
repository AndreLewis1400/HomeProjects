<!DOCTYPE html>
<html>
<head>
    <title>My Simple Website</title>
</head>
<body>
    <h1>Welcome to My Website</h1>
    <p>This is a basic example of a website with JavaScript.</p>
    
    <button id="myButton">Click me!</button>
    <p id="message"></p>

    <script>
        // JavaScript code embedded in the HTML file
        // This code will run when the page loads
        document.getElementById("myButton").addEventListener("click", function() {
            document.getElementById("message").innerHTML = "Hello, World!";
        });
    </script>

    <hr>

    <h2>About Us</h2>
    <p>We are a team of developers creating amazing web experiences.</p>

    <hr>

    <h2>Contact Information</h2>
    <ul>
        <li>Email: contact@example.com</li>
        <li>Phone: +1 (123) 456-7890</li>
        <li>Address: 123 Main Street, Cityville</li>
    </ul>

    <hr>

    <h2>Services</h2>
    <ul>
        <li>Web Design</li>
        <li>Web Development</li>
        <li>SEO Optimization</li>
    </ul>

    <hr>

    <h2>Testimonials</h2>
    <blockquote>
        <p>"This website is fantastic! I love the interactive features."</p>
        <cite>- Happy Visitor</cite>
    </blockquote>

    <blockquote>
        <p>"The team behind this website is top-notch. Great job!"</p>
        <cite>- Another Satisfied User</cite>
    </blockquote>

    <hr>

    <h2>Latest News</h2>
    <ul>
        <li>Check out our new blog post: "10 Tips for Web Development"</li>
        <li>Join our newsletter for the latest updates and offers.</li>
    </ul>

    <hr>

    <footer>
        <p>&copy; 2023 My Simple Website</p>
    </footer>
</body>
</html>