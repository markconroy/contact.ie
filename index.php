<?php
  $emails = array('mark@contact.ie, info@contact.ie, help@contact.ie, list@contact.ie, new@contact.ie');
  $subject = 'A subject line';
  $message = 'This is my message to you, Rudy';
?>

<form action="mailto:
  <?php foreach ($emails as $email): ?>
    <?php print $email . ','; ?>
  <?php endforeach; ?>" method="GET">
  <div>
    <p>Who do you want to email?</p>
    <select>
      <option>All TDs</option>
      <option>All Senators</option>
    </select>
  <div>
    <p>What is the Subject of the Email?</p>
    <input name="subject" type="text" />
  </div>
  <p>Type your message here:</p>
  <div>
    <textarea name="body"></textarea>
  </div>
  <div>
    <input type="submit" value="Send Email" />
  </div>
</form>
