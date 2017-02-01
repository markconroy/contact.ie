$(document).ready(function() {
  $(".fianna-fail").click(function() {
    $("#form").load("/contacts/political-parties/fianna-fail/index.php");
  });
  $(".fine-gael").click(function() {
    $("#form").load("/contacts/political-parties/fine-gael/index.php");
  });
});
