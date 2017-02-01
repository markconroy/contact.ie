<?php

/**
 * @file
 * This is the main file used to pull the necessary items to create the forms.
 */

  include $_SERVER["DOCUMENT_ROOT"] . '/inc/email-addresses.php';
?>

<?php $emails = $email_addresses['Political Parties']['Fianna Fail']; ?>

<?php include $_SERVER["DOCUMENT_ROOT"] . '/inc/form.php'; ?>
