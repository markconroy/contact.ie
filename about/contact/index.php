<?php
/**
 *  Copyright (C) 2017 Mark Conroy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SUPPLEMENTARY RESTRICTION BY MARK CONROY, AUTHOR OF CURRENT Work
 * WHILST I AM MAKING THIS CODE FREELY AVAILABLE FOR USE, I AM RESTRICTING
 * THE USE OF IT FOR ANY PURPOSES THAT MIGHT BE CONSIDERED 'ALT-RIGHT' OR
 * 'FAR RIGHT'. TO BE CLEAR, YOU MAY NOT CREATE SOMETHING FROM THIS SOFTWARE
 * THAT MAY BE USED TO SUPPORT OR PROMOTE RACISM, PREJUDICE, HATRED, FASCISM,
 * ETC.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<?php

/**
 * @file
 * This file creates the "About Us" page.
 */

$title = "Contact Contact.ie";
$description = "Get in Contact with Contact.ie";
?>

<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/head-n-header.php'; ?>
<main class="layout-contained padding">
  <h1>Contact Contact.ie</h1>
  <p>Please be aware, Contact.ie is fully volunteer run in our spare time. We may not have time to respond to you; if this is the case, we are sorry.</p>
  <p>We have:
    <ul>
      <li>an email address: info@contact.ie</li>
      <li>a Twitter account: <a href="https://twitter.com/contact_ie">@contact_ie</a></li>
      <li>a Facebook page: <a href="http://facebook.com/contact.ie/">facebook.com/contact.ie</a></li>
    </ul>
  </p>
  <?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/faqs.php'; ?>
</main>
<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/footer.php'; ?>
