-- SUMMARY --

This module augments Drupal Core's Statistics module by exposing additional
fields for inclusion in the Access Log and providing an API for other modules
to also collect arbitrary data.

This module requires the Statistics module be enabled and "Enable access log"
checked at admin/config/system/statistics.


-- FEATURES --

* Provides cache status, user-agent, and peak memory fields for the access log.
* Integrates additional fields with views (filtering, sorting, etc).
* Provides an API for other modules to collect arbitrary data in the access log.
* Additions to the core Statistics configuration page allowing users to
  customize which fields to enable for data collection.


-- INSTALLATION --

* Ensure that the core Statistics module is already enabled.
* Install and enable this module.
* Configure custom access log data collection at admin/config/system/statistics.
