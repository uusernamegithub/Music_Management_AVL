# Music_Management_AVL
<h1>Audiobook Library System</h1><br>
<p>The Audiobook Library System is a software solution designed to efficiently manage a collection of audiobooks and user interactions. It utilizes AVL Tree data structure to organize audiobooks and user profiles, allowing for quick access to audiobooks, effective tracking of listening progress, and support for user preferences and libraries.</p><br>

<h2>User Tree Structure</h2><br>
<p>Each user in the system is represented by the following fields:</p><br>
<ul>
    <li><strong>UserID</strong>: A unique identifier for each user.</li><br>
    <li><strong>Name</strong>: The name of the user.</li><br>
    <li><strong>Email</strong>: The email address of the user (unique within the system).</li><br>
    <li><strong>Preferences</strong>: User preferences, which could include preferred genres, authors, narrators, or other audiobook characteristics.</li><br>
    <li><strong>Audiobook log</strong>: A refrence to another tree for user's audiobook Library,sorted by Audiobook ID.</li><br>
</ul><br>

<h2>Audiobook  Tree Structure</h2><br>
<p>Each audiobook in the system is represented by the following fields:</p><br>
<ul>
    <li><strong>AudiobookID</strong>: A unique identifier for each audiobook.</li><br>
    <li><strong>Title</strong>: The title of the audiobook.</li><br>
    <li><strong>Author</strong>: The name(s) of the author(s) of the audiobook.</li><br>
    <li><strong>Narrator</strong>: The person or people who narrate the audiobook.</li><br>
    <li><strong>Duration</strong>: The total length of the audiobook, typically in hours and minutes.</li><br>
    <li><strong>Genre</strong>: The category or type of content the audiobook falls under, such as fiction, non-fiction, science fiction, etc.</li><br>
    <li><strong>sum_Rating</strong>: A variable to store total sum score reflecting user feedback and preferences.</li><br>
      <li><strong>count_Rating</strong>: A variable to store number of users rated.</li><br>
</ul><br>

<h2>Functionality</h2><br>
<p>The Audiobook Library System provides the following functionalities:</p><br>
<ol>
    <li><strong>Add Audiobook and Edit Audiobook</strong>: Add new audiobooks to the library or edit existing audiobook details.</li><br>
    <li><strong>Delete Audiobook</strong>: Remove audiobooks from the library based on specified criteria.</li><br>
    <li><strong>Search Audiobook</strong>: Search for audiobooks based on various criteria such as title, author, or genre.</li><br>
    <li><strong>Add User Profile</strong>: Create new user profiles with name, email, and preferences.</li><br>
    <li><strong>Add to User Library</strong>: Allow users to add or remove audiobooks from their personal library.</li><br>
    <li><strong>Listening Progress</strong>: Track the listening progress of users for each audiobook.</li><br>
    <li><strong>Display User Libraries</strong>: View the audiobook collections of users based on different filters.</li><br>
    <li><strong>Rate Audiobook</strong>: Allow users to rate audiobooks, contributing to their overall feedback score.</li><br>
    <li><strong>Most Popular Audiobook</strong>: Determine the most popular audiobook based on user ratings.</li><br>
    <li><strong>Listening History Report (User)</strong>: Generate a report detailing the audiobooks listened to by a specific user.</li><br>
    <li><strong>Listening History Report (Audiobook)</strong>: Generate a report detailing the listening history of a specific audiobook.</li><br>
    <li><strong>Display Audiobook List with Average Rating</strong>: Display the list of audiobooks sorted by title with their average ratings.</li><br>
</ol><br>

<h2>Implementation</h2><br>
<p>The system is implemented in C programming language using a AVL tree data structure for efficient management of audiobooks and user profiles. Each functionality is implemented as a separate function, with a main function handling user input and interaction.</p><br>

<h2>File Handling</h2><br>
<p>File handling is utilized to read initial data from a .txt file containing user and audiobook information. This allows for easy initialization of the system with pre-existing data.</p><br>


