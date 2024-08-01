<?php

/**
 * @file
 */

$dates = [
  "03/2023",
  "12/2021",
  "11/2012",
  "12/2022",
  "06/2023",
  "1/2012",
];

$last = end($dates);
$mostRecentTimestamp = 0;
foreach ($dates as $date) {
  $dateParts = explode("/", $date);
  $formatted = $dateParts[1] . '-' . $dateParts[0];
  var_dump($formatted);
  $timestamp = strtotime($formatted);
  var_dump($dateParts);
  var_dump($timestamp);
  if ($timestamp > $mostRecentTimestamp) {
    $last = $date;
    $mostRecentTimestamp = $timestamp;
  }
}

var_dump($last);
