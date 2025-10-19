# MenuMap Presentation Talking Points
## CEN4010 Software Engineering - Team 9

**Presenter:** Andre Lewis (UML Diagrams Coordinator)  
**Project:** MenuMap Application  
**Team:** Team 9  
**Project Lead:** Alfonso Oramas Jr.  

---

## 🎤 **Opening (2 minutes)**

### **Introduction**
"Good morning/afternoon everyone. I'm Andre Lewis, and I'm the UML Diagrams Coordinator for Team 9. Today I'll be presenting our MenuMap application, a restaurant discovery and menu management system that we've developed for CEN4010 Software Engineering."

### **Team Introduction**
"Our team consists of Alfonso Oramas Jr. as our Project Lead, myself as the UML Diagrams Coordinator, and our team members Eve, Alex, and Kamal. Each of us has specific responsibilities in this project."

---

## 🍽️ **Use Cases Section (5 minutes)**

### **Slide 5: UC-001 - Browse Restaurant Menus**

**Opening:**
"Let me walk you through our three use cases. First, we have UC-001: Browse Restaurant Menus."

**Key Points:**
- "This is a normal use case that allows users to search and browse restaurant menus by cuisine, location, or specific items"
- "The actors involved are the User as the primary actor, Restaurant Owner as a secondary actor, and our MenuMap System"
- "Here's a scenario: Sarah is looking for Italian restaurants. She opens MenuMap, types 'Italian' in the search bar, and the system displays 15 Italian restaurants within 5 miles. She finds Mario's Italian Bistro with 4.5 stars, taps on it, and sees the complete menu with categories like pasta, pizza, and desserts."
- "Another scenario shows Mike, a college student on a budget, using the cuisine filter to find affordable Mexican food. He sorts by price and finds Local Taqueria with a Bean Burrito for $6.99."
- "Lisa, a vegetarian, searches for 'vegetarian burger' and finds Green Garden Cafe with a Veggie Deluxe Burger for $12.99."

**Transition:**
"This use case demonstrates our system's core functionality for restaurant discovery."

### **Slide 6: UC-002 - Manage Favorites**

**Opening:**
"Next, we have UC-002: Manage Favorites, which enables registered users to save and organize their favorite restaurants and menu items."

**Key Points:**
- "The primary actor is a Registered User, and the system actor is our MenuMap System"
- "David, a regular customer, adds Tony's Pizza to his favorites by tapping the heart button. The system confirms 'Added to Favorites!' and he can now quickly access it anytime."
- "Maria, a food blogger, organizes her 20 favorite restaurants into categories like 'Breakfast Spots' and 'Date Night' using our drag-and-drop interface."
- "Alex, who's health-conscious, adds his favorite Quinoa Power Bowl to a 'Healthy Meals' category for quick reordering."

**Transition:**
"This use case shows how we enhance user experience through personalization."

### **Slide 7: UC-003 - Secure Password Reset**

**Opening:**
"Our third use case is UC-003: Secure Password Reset, which is our security use case that addresses misuse cases and fraud prevention."

**Key Points:**
- "This involves the User as primary actor, MenuMap System, and Email Service as external actor"
- "Jennifer forgot her password after not using MenuMap for months. She clicks 'Forgot Password?', enters her email, and receives a secure reset link. She sets a new password 'NewSecurePass123!' and regains access."
- "Tom tries to reset with a wrong email 'tom@wrongemail.com'. Our system protects against email enumeration by showing a generic message 'If this email exists, you'll receive a reset link' without revealing whether the email exists."
- "Robert clicks an expired reset link after 2 days. Our system enforces a 24-hour expiration and prompts him to request a new reset."
- "Key security features include token-based security with 24-hour expiration, rate limiting to prevent abuse, audit logging for security monitoring, and fraud prevention measures."

**Transition:**
"This security use case demonstrates our commitment to protecting user data and preventing misuse."

---

## 📊 **UML Diagrams Section (3 minutes)**

### **Slide 9: UML Diagrams Overview**

**Opening:**
"Now let me show you our UML diagrams that support these use cases."

**Key Points:**
- "We created individual use case diagrams for each of our three use cases using Papyrus, as required by the assignment"
- "Here's the diagram for UC-001 showing the User, Restaurant Owner, and System actors connected to the Browse Restaurant Menus use case"
- "UC-002 shows the Registered User and System actors for the Manage Favorites use case"
- "UC-003 demonstrates our security use case with User, System, and Email Service actors for Secure Password Reset"
- "Our Class Diagram shows the system structure with User Management, Restaurant & Menu classes, Favorites & User Preferences, and Security & Verification components"
- "The User Login Sequence Diagram illustrates the dynamic behavior of our authentication process"

**Technical Details:**
- "All diagrams were created using Eclipse Papyrus, following UML standards"
- "Each use case diagram clearly shows the actors, use cases, and their relationships"
- "The diagrams support our use cases by visualizing the system interactions and structure"

---

## 🎯 **Key Achievements (2 minutes)**

### **What We Delivered:**
- "We have exactly what was required: 2 normal use cases and 1 security use case"
- "Each use case has its own individual Papyrus diagram"
- "We created comprehensive scenarios for each use case, demonstrating real-world usage"
- "Our security use case specifically addresses misuse cases and fraud prevention"
- "All UML diagrams follow proper standards and support our use cases"

### **Technical Excellence:**
- "Our use cases cover the complete user journey from discovery to personalization to security"
- "The scenarios show different user types and edge cases"
- "Our security implementation includes industry-standard practices like token expiration and rate limiting"

---

## 🏁 **Closing (1 minute)**

### **Summary:**
"In conclusion, our MenuMap application demonstrates a comprehensive understanding of software engineering principles. We have three well-defined use cases with detailed scenarios, complete UML documentation using Papyrus, and a security-focused approach that addresses real-world concerns."

### **Team Collaboration:**
"This project showcases effective team collaboration with clear roles and responsibilities. As the UML Diagrams Coordinator, I worked closely with our Project Lead Alfonso and team members Eve, Alex, and Kamal to deliver a complete solution."

### **Thank You:**
"Thank you for your attention. Our MenuMap application is ready for implementation and addresses real market needs in restaurant discovery and menu management. Are there any questions?"

---

## 📋 **Presentation Tips**

### **Delivery:**
- Speak clearly and confidently
- Make eye contact with the audience
- Use the slides as visual aids, not reading material
- Pause between sections for emphasis
- Use hand gestures to point to diagrams

### **Timing:**
- **Opening:** 2 minutes
- **Use Cases:** 5 minutes (about 1.5 minutes per use case)
- **UML Diagrams:** 3 minutes
- **Key Achievements:** 2 minutes
- **Closing:** 1 minute
- **Total:** 13 minutes (leaving 2 minutes for questions)

### **Key Messages to Emphasize:**
1. **Three Use Cases:** Exactly what was required
2. **Individual Diagrams:** Each use case has its own Papyrus diagram
3. **Security Focus:** Our security use case addresses misuse cases
4. **Real Scenarios:** Practical examples with different user types
5. **Team Collaboration:** Clear roles and effective teamwork

---

## 🎤 **Practice Points**

### **Before the Presentation:**
- Practice each section out loud
- Time yourself to stay within limits
- Review the scenarios until you can tell them naturally
- Familiarize yourself with the UML diagrams
- Prepare for potential questions about security features

### **Common Questions to Expect:**
- "How does your security use case prevent fraud?"
- "Why did you choose these specific use cases?"
- "How do the UML diagrams support your use cases?"
- "What makes your approach different from existing apps?"

### **Answers Ready:**
- Security: Token expiration, rate limiting, audit logging, no email enumeration
- Use Cases: Cover core functionality (discovery, personalization, security)
- UML: Visual representation of system structure and behavior
- Differentiation: Focus on security, comprehensive scenarios, detailed documentation

---

*Use these talking points as a guide. Practice until you can deliver them naturally and confidently. Good luck with your presentation!*
