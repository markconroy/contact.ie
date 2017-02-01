<form action="mailto:
  <?php foreach ($emails as $email): ?>
    <?php print $email . ','; ?>
  <?php endforeach; ?>" method="GET" target="_blank">
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
