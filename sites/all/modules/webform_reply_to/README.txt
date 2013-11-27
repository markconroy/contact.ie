Description 
----------- 
This module adds a Reply-To header to E-mail sent by the Webform module.

A Reply-To header is helpful if you are worried that the 'e-mail from 
address' setting will cause the e-mail sent by Webform to be marked as 
spam by e-mail clients, since the resulting From: address and the sender's
actual origination address will not match.  To fix this, you can make the
'e-mail from address' match the address of your Drupal server; however the
recipient of the e-mail will then be unable to simply use the 'reply' button
on the e-mail client to respond.  By setting a Reply-To header, your e-mail
will not be marked as spam since the sender information will match, but the
e-mail recipient will again be able to use the 'reply' button in their e-mail
client.

Requirements
------------
Drupal 7.x
Webform 7.x-3.x

Installation
------------
1. Copy the entire webform_reply_to directory to the Drupal
   sites/all/modules directory.

2. Login as an administrator. Enable the module on the "Administer" ->
   "Modules" page.

3. Add a Reply-To for each desired Webform in its "E-mail Settings".

Support
-------
Please use the issue queue for filing bugs with this module at
http://drupal.org/project/issues/webform_reply_to

Sponsor
-------
This module development has been sponsored by GroupTracks. If you are 
interested in having this module customized, you can reach us at 
drupal@grouptracks.com. 
