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
 * This file presents a list of email addresses for TDs by political party.
 */

$title = "List of Email Addresses for TDs by Political Party";
$description = "Find the email address of any/all TDs by political party in Ireland";
?>
<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/head-n-header.php'; ?>
<main class="layout-contained padding">
  <h1>List of Email Addresses for TDs by Political Party</h1>

  <ul>
    <?php
    $file = file_get_contents($_SERVER['DOCUMENT_ROOT'] . '/assets/emails/parties.json');
    $items = json_decode($file, TRUE);
    foreach ($items as $item) {

      $email_addresses = $item['emails'];
      print $item['party_name'];
      print '<ul>';
      foreach ($email_addresses as $email_address) {
        print '<li>' . $email_address . '</li>';
      }
      print '</ul>';
    }
    ?>
  </ul>

</main>
<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/footer.php'; ?>
