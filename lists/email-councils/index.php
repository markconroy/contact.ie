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
 * This file presents a list of email addresses for Town and County Councillors.
 */

$title = "List of Email Addresses for Town and County Councillors";
$description = "Find the email address of any/all town or county councillor in Ireland";
?>
<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/head-n-header.php'; ?>
<main class="layout-contained padding">
  <h1><?php print $title; ?></h1>

  <ul>
    <?php
    $file = file_get_contents($_SERVER['DOCUMENT_ROOT'] . '/assets/emails/councils.json');
    $items = json_decode($file, TRUE);
    foreach ($items as $item) {

      $email_addresses = $item['emails'];
	  $mundistricts = $item['district'];
	  
	  if ($mundistricts === "") {
		  print $item['council_name'];
		  print '<ul>';
		  foreach ($email_addresses as $email_address) {
			print '<li>' . $email_address . '</li>';
		  }
		  print '</ul>';
	  }else{
		  print '<h3>' . $item['council_name'] . '</h3><br>';
		  foreach ($mundistricts as $district => $emailAddr) {
			print $district;
			print '<ul>';
			for ($i=0;$i<count($emailAddr);$i++){
				print '<li>' . $emailAddr[$i] . '</li>';
			}
			print '</ul>';
		  }
		  print '</ul>';	  
	  }
    }
    ?>
  </ul>

</main>
<?php include $_SERVER['DOCUMENT_ROOT'] . '/includes/footer.php'; ?>
