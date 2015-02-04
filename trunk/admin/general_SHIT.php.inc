<?php

function display_manage_music_form ($music_id = 0, $init_artist = '', $init_album = '', $init_day = 0, $init_month = 0, $init_year = 0, $init_picture_url = 'http://www.sprucegooserecords.com/', $init_artist_url = 'http://www.sprucegooserecords.com/store/', $init_store_url = 'http://www.sprucegooserecords.com/store/', $init_download_id = 0, $init_free_download = 1, $init_featured = 1, $init_updatedescr = '', $new = 1, $init_enabled = 1) {

  if ($init_day == 0) $init_day = (int)date("d");
  if ($init_month == 0) $init_month = (int)date("m");
  if ($init_year == 0) $init_year = (int)date("Y");

  $text_width = "400px";

  if ($new) { $fmusic = 'fmusic'; } else { $fmusic = 'fupdatemusic'; }
  echo "<form name='$fmusic' action='' method='post'>\n
        <table>\n
        <input type='hidden' name='music_id' value='$music_id' />\n
        <tr><td style='text-align:right;'>Artist:</td><td><input style='width:$text_width;' type='textbox' name='artist_name' value=\"$init_artist\" /></td></tr>\n
        <tr><td style='text-align:right;'>Album:</td><td><input style='width:$text_width;' type='textbox' name='album_name' value=\"$init_album\" /></td></tr>\n
        <tr><td style='text-align:right;'>Release Date:</td><td>\n
        <select name='album_day'>\n";

  for($day=1; $day <= 31; $day++) {
    echo "<option value='" .date("d", mktime(date("H"), date("i"), date("s"), $month, $day, date("Y"))). "'";
    if($day == $init_day) echo " selected";
    echo ">$day</option>\n";
  }
  echo "</select>\n&nbsp;
        <select name='album_month'>\n";
  for($month=1; $month <= 12; $month++) {
    echo "<option value='" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "'";
    if ($month == $init_month) echo " selected";
    echo ">" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))) ." - ". date("F", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "</option>\n";
  }
  echo "</select>\n&nbsp;
        <select name='album_year'>\n";
  for ($year=1+(int)date("Y"); $year >= 1990; $year--) {
    echo "<option value='" .$year. "'";
    if($year == $init_year) echo " selected";
    echo ">" .$year. "</option>\n";
  }
  echo "</select>
        </td></tr>\n";

  echo "<tr><td style='text-align:right;'>Album Art (Front) Hot Link (URL):</td><td><input style='width:$text_width;' type='textbox' name='picture_url' value=\"$init_picture_url\" /></td></tr>\n
        <tr><td style='text-align:right;'>Store URL:</td><td><input style='width:$text_width;' type='textbox' name='store_url' value=\"$init_store_url\" /></td></tr>\n
        <tr><td style='text-align:right;'>Artist URL:</td><td><input style='width:$text_width;' type='textbox' name='artist_url' value=\"$init_artist_url\" /></td></tr>\n";

  echo "<tr><td style='text-align:right;'>Download ID:</td>\n
          <td>\n
            <select name='download_id'>\n";

  $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_FILE_DOWNLOAD];
  $query = "SELECT *
            FROM $thetable";
  $num = $wpdb->query($query);

  if($num === FALSE) {
    wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
  } else {
    for($i=0; $i <= $num; $i++) {
      $row = $wpdb->get_row($query, ARRAY_A, $i);
      if ($i > 0) {
        $file_name = $row['file_name'];
        $download_count = $row['download_count'];
        $arrayFile = explode("/", $file_name);
        $arrayFile = array_reverse($arrayFile);
        $file_name = $arrayFile[0];
      }
      echo "<option value='$i'";
      if ($i == $init_download_id) echo " selected";
      echo ">";
      echo ($i == 0) ? "Don't Link It Right Now" : "$i - $file_name";
      echo "</option>\n";
    }
  }
  echo "    </select>\n
          </td>\n
        </tr>\n
        <tr><td style='text-align:right;'>Free Download:</td><td><input style='width:$text_width' type='checkbox' name='free_download_enabled'";
  if ($init_free_download) { echo ' checked '; }
  echo "/></td></tr>\n
        <tr><td style='text-align:right;'>Featured:</td><td><input style='width:$text_width' type='checkbox' name='featured'";
  if ($init_featured) { echo ' checked '; }
  echo "/></td></tr>\n
        <tr><td style='text-align:right;'>Enabled:</td><td><input style='width:$text_width' type='checkbox' name='enabled'";
  if ($init_enabled) { echo ' checked '; }
  echo "/></td></tr>\n
        <tr><td style='text-align:right;'>Description:</td><td><textarea name='updatedescr'>$init_updatedescr</textarea></td></tr>\n
        <tr><td colspan='2'></td></tr>\n";
  if ($new) {
    echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='new' value='Add New Album' /></td></tr>\n";
  } else {
    echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='update' value='Update Album' /></td></tr>\n";
  }

  echo "</table>
        </form>\n";
}

function display_manage_artist_form ($artist_id = 0, $init_artist = '', $init_day = 0, $init_month = 0, $init_year = 0, $init_picture_url = '/', $init_artist_url = '/', $init_artist_descr = '', $new = 1) {

  if ($init_day == 0) $init_day = (int)date("d");
  if ($init_month == 0) $init_month = (int)date("m");
  if ($init_year == 0) $init_year = (int)date("Y");

  $text_width = "400px";

  if ($new) { $fartist = 'fartist'; } else { $fartist = 'fupdateartist'; }
  echo "<form name='$fartist' action='' method='post'>
        <table>\n
        <input type='hidden' name='artist_id' value='$artist_id' />\n
        <tr><td style='text-align:right;'>Artist:</td><td><input style='width:$text_width;' type='textbox' name='artist_name' value='$init_artist' /></td></tr>\n
        <tr><td style='text-align:right;'>Birthday:</td><td>\n
        <select name='artist_day'>\n";
  for($day=1; $day <= 31; $day++) {
    echo "<option value='" .date("d", mktime(date("H"), date("i"), date("s"), $month, $day, date("Y"))). "'";
    if($day == $init_day) echo " selected";
    echo ">$day</option>\n";
  }
  echo "</select>\n&nbsp;
        <select name='artist_month'>\n";
  for($month=1; $month <= 12; $month++) {
    echo "<option value='" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "'";
    if ($month == $init_month) echo " selected";
    echo ">" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))) ." - ". date("F", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "</option>\n";
  }
  echo "</select>\n&nbsp;
        <select name='artist_year'>\n";
  for ($year=1+(int)date("Y"); $year >= 1930; $year--) {
    echo "<option value='" .$year. "'";
    if($year == $init_year) echo " selected";
    echo ">" .$year. "</option>\n";
  }
  echo "</select>\n
        </td></tr>\n";

  echo "<tr><td style='text-align:right;'>Picture (URL):</td><td><input style='width:$text_width;' type='textbox' name='picture_url' value=\"$init_picture_url\" /></td></tr>\n
        <tr><td style='text-align:right;'>Artist (URL):</td><td><input style='width:$text_width;' type='textbox' name='artist_url' value=\"$init_artist_url\" /></td></tr>\n
        <tr><td style='text-align:right;'>Description:</td><td><textarea name='artist_descr'>$init_artist_descr</textarea></td></tr>\n
        <tr><td colspan='2'></td></tr>\n";
  if ($new) {
    echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='new' value='Add New Artist' /></td></tr>\n";
  } else {
    echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='update' value='Update Artist' /></td></tr>\n";
  }

  echo "</table>\n
        </form>\n";
}

function display_manage_discography_form ($artist_id = 0, $init_artist = '', $init_picture_url = 'http://www.sprucegooserecords.com/', $init_artist_url = 'http://www.sprucegooserecords.com/store/') {
  $text_width = "400px";
  $faalinker = 'fupdatelinker';

  echo "<center>\n
        <form name='$faalinker' action='' method='post'>\n
        <table>\n
        <tr><td colspan='2' style='text-align:center;font-weight:bold;'><a href='$init_artist_url'>$init_artist</a></td></tr>\n
        <input type='hidden' name='artist_id' value='$artist_id' />\n";

  $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_MUSIC_ALBUMS];
  $query = "SELECT *
            FROM $thetable
            ORDER BY album_date DESC";
  $num = $wpdb->query($query);

  if($num === FALSE) {
    wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
  } else {
    $row = $wpdb->get_row($query, ARRAY_A, 0);
    $cols = 4;
    $rows = ((int)($num / $cols) < (float)($num / $cols)) ? (int)($num / $cols) + 1 : (int)($num / $cols);

    $width = '150px';
    $height = '150px';

    echo "    <table border='0'>\n";
    if ($num === 0) {
      echo "    <tr>\n
                  <td colspan='$cols' style='border:none;'>" .__('No Music Available in the Database!', $i18n_domain). "</td>\n
                </tr>\n";
    } else {
      for ($i = 0; $i < $rows; $i++) {
        echo "      <tr>\n";
        for($j = 0; $j < $cols && ((($cols * ($i)) + ($j+1)) <= $num); $j++) {
          $album_id = $row['id'];
          $picture_url = stripslashes($row['picture_url']);
          $download_id = stripslashes($row['download_id']);
          $artist_name = stripslashes($row['artist_name']);
          $album_name = stripslashes($row['album_name']);
          $album_date = stripslashes($row['album_date']);
          $artist_url = stripslashes($row['artist_url']);
          $store_url = stripslashes($row['store_url']);
          $free_download_enabled = $row['free_download_enabled'];
          $featured = $row['featured'];
          $updatedescr = stripslashes($row['updatedescr']);

          $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_ALBUM_LINKER];
          $query = "SELECT *
                    FROM $thetable
                    WHERE artist_id='$artist_id'
                      AND album_id='$album_id'";
          $num2 = $wpdb->query($query);

          if($num2 === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
          } else {
            $row2 = $wpdb->get_row($query, ARRAY_A, $j);
            if ($num2 > 0) {
              $album_checked = 'checked ';
            } else {
              $album_checked = '';
            }
            echo "          <td style='border:0;'>\n
                              <div>\n
                                <center><font style='font-size:8pt'>\n
                                <a href='$artist_url'>$artist_name</a><br/>\n
                                <a href='$store_url'>$album_name</a><br/>\n
                                <a href='$store_url' target='_blank'><img src='$picture_url' style='border:1px solid black;height:$height;width:$width;' /></a><br/>\n
                                <input type='checkbox' name='album_$album_id' $album_checked/>Link this Album<br/>\n
                                </font></center>\n
                              </div>\n
                            </td>\n";
          }
        }
        for($j; $j < $cols; $j++) {
          echo "<td>&nbsp;</td>\n";
        }
        echo "      </tr>\n";
        if ($i < ($rows-1)) { echo "<tr><td colspan='$cols'><hr style='width:100%;'></td></tr>\n"; }
      }
    }
  }

  echo "<tr><td colspan='2'></td></tr>
        <tr><td colspan='2' style='text-align:center;'><input type='submit' name='update' value='Update Artist Album Features' /></td></tr>\n
        </table>
        </form>
        </center>";
}

function display_artist_discography ($artist_id = 0) {

  $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_MUSIC_ALBUMS];
  $thetable2 = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_ALBUM_LINKER];
  $query = "SELECT *
            FROM $thetable
            WHERE id IN (SELECT album_id
                         FROM $thetable2
                         WHERE artist_id=$artist_id
                           AND enabled=1)
            ORDER BY album_date DESC";
  $num = $wpdb->query($query);
  if($num === FALSE) {
    wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
  } else {
    $cols = 1;
    $rows = ((int)($num / $cols) < (float)($num / $cols)) ? (int)($num / $cols) + 1 : (int)($num / $cols);
    $width = '225px'; //'150px';
    $height = '225px'; //'150px';

    $discog_html .= "    <center>
                         <table border='0'>\n";
    if ($num == 0) {
      $discog_html .= "    <tr>
                             <td colspan='$cols' style='border:none;'>" .__('No Music Available in the Database!', $i18n_domain). "</td>
                           </tr>\n";
    } else {
      for ($i = 0; $i < $rows; $i++) {
        $discog_html .= "      <tr>\n";
        for($j = 0; $j < $cols && ((($cols * ($i)) + ($j+1)) <= $num); $j++) {
          $row = $wpdb->get_row($query, ARRAY_A, $j);

          $id = $row['id'];
          $picture_url = stripslashes($row['picture_url']);
          $download_id = stripslashes($row['download_id']);
          $artist_id = NULL;
          $artist_name = stripslashes($row['artist_name']);
          $album_name = stripslashes($row['album_name']);
          $album_date = stripslashes($row['album_date']);
          $artist_url = stripslashes($row['artist_url']);
          $store_url = stripslashes($row['store_url']);
          $free_download_enabled = $row['free_download_enabled'];
          $featured = $row['featured'];
          $updatedescr = stripslashes($row['updatedescr']);

          $released = date("M",mktime(0,0,0,(int)substr($album_date, 5, 2), (int)substr($album_date, 8, 2), (int)substr($album_date, 0, 4))). "." .substr($album_date, 8, 2). "." .substr($album_date, 0, 4);
          $discog_html .= "        <td style='border:0;'>\n
                                     <center><font style='font-size:8pt'>\n
                                     <a href='$artist_url' alt='$artist_name' title='$artist_name'>$artist_name</a><br/>\n
                                     <a href='$store_url' alt='$released - $artist_name - $album_name' title='$released - $artist_name - $album_name'>$album_name</a><br/>\n
                                     <a href='$store_url' target='_blank'><img src='$picture_url' style='border:1px solid black;height:$height;width:$width;' alt='" .$released. " - $artist_name - $album_name' title='" .$released. " - $artist_name - $album_name' /></a><br/>\n
                                     Released: " .date("M",mktime(0,0,0,(int)substr($album_date, 5, 2), (int)substr($album_date, 8, 2), (int)substr($album_date, 0, 4))). "." .substr($album_date, 8, 2). ".<a href='#' target='_blank'>" .substr($album_date, 0, 4). "</a><br/>\n
                                     <a href='http://www.sprucegooserecords.com/download.php?id=$download_id' target='_blank'><img width='112' height='75' src='http://sprucegooserecords.com/images/download.grey.icon.jpg' /></a>\n
                                     </font></center>\n
                                 </td>\n
                                 <td style='border:0;'>\n
                                     <div class='tracklist'>\n
                                     <font style='font-size:8pt'>\n
                                       $updatedescr\n
                                     </font>\n
                                     </div>\n
                                 </td>\n";
        }
        for($j; $j < $cols; $j++) {
          $discog_html .= "<td>&nbsp;</td>\n";
        }
        $discog_html .= "      </tr>\n";
        if ($i < ($rows-1)) { $discog_html .= "<tr><td colspan='" .($cols*2). "'><hr style='width:100%;'></td></tr>\n"; }
      }
    }
    $discog_html .= "    </table>
                         </center>\n";
  }

  return $discog_html;
}

?>
