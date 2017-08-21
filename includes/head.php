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

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="UTF-8">
    <title><?php print $title; ?> | Contact.ie</title>
    <meta name="description" content="<?php print $description; ?>">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <meta name="msapplication-tap-highlight" content="no">
    <link rel="icon" type="image/x-icon" href="assets/icon/favicon.ico">
    <link rel="shortcut icon" href="/favicons/favicon.ico" type="image/x-icon" />
    <meta name="apple-mobile-web-app-capable" content="yes" />
    <meta name="msapplication-TileColor" content="#CD4945" />
    <meta name="msapplication-TileImage" content="/themes/custom/patternlab/images/favicons/ms-icon-144x144.png" />
    <meta name="theme-color" content="#CD4945" />
    <link rel="apple-touch-icon" sizes="57x57" href="/favicons/apple-icon-57x57.png" />
    <link rel="apple-touch-icon" sizes="60x60" href="/favicons/apple-icon-60x60.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/favicons/apple-icon-72x72.png" />
    <link rel="apple-touch-icon" sizes="76x76" href="/favicons/apple-icon-76x76.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/favicons/apple-icon-114x114.png" />
    <link rel="apple-touch-icon" sizes="120x120" href="/favicons/apple-icon-120x120.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/favicons/apple-icon-144x144.png" />
    <link rel="apple-touch-icon" sizes="152x152" href="/favicons/apple-icon-152x152.png" />
    <link rel="apple-touch-icon" sizes="180x180" href="/favicons/apple-icon-180x180.png" />
    <link rel="icon" sizes="192x192" href="/favicons/android-icon-192x192.png" type="image/png" />
    <link rel="icon" sizes="32x32" href="/favicons/favicon-32x32.png" type="image/png" />
    <link rel="icon" sizes="96x96" href="/favicons/favicon-96x96.png" type="image/png" />
    <link rel="icon" sizes="16x16" href="/favicons/favicon-16x16.png" type="image/png" />
    <link rel="icon" sizes="16x16" href="/favicons/favicon.ico" type="image/png" />
    <link rel="manifest" href="manifest.json">
    <link rel="stylesheet" href="/css/style.css">
    <script>
      if ('serviceWorker' in navigator) {
        navigator.serviceWorker.register('service-worker.js')
          .then(() => console.log('service worker installed'))
          .catch(err => console.log('Error', err));
      }
    </script>
  </head>
