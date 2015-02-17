<?php
$music = new Music;

if (strcmp($_POST['update'], NULL)) {
    if ($music->updateById($_POST['music_id'],
                           $_POST['artist_id'],
                           $_POST['artist_name'],
                           $_POST['album_name'],
                           $music->formatDateTime($_POST['album_day'], $_POST['album_month'], $_POST['album_year']),
                           $_POST['artist_url'],
                           $_POST['picture_url'],
                           $_POST['store_url'],
			   $_POST['price'],
                           $_POST['download_id'],
                           $_POST['description']) ) {
        _e("The album was successfully updated in the database!<br/>\n", $i18n_domain);
    } else {
        _e("A problem occurred while trying to update the album and the update information was lost!<br/>\n", $i18n_domain);
    }
}
else if (strcmp($_POST['edit'], NULL) && strcmp($_POST['edit'], '0')) {

    if (!strcmp($_POST['update'], NULL)) {
        $music->loadById($_POST['edit']);

        if($music->getTotalRows() > 0) {

            $music->display_manage_music_form ($music->id,
                                               $music->artist_name,
                                               $music->album_name,
                                               $music->album_day, $music->album_month, $music->album_year,
                                               $music->picture_url,
                                               $music->artist_url,
                                               $music->store_url,
                                               $music->price,
					       $music->download_id,
                                               $music->description,
                                               FALSE );
        }
    }
} else if (strcmp($_POST['new'], NULL) && strcmp($_POST['artist_name'], NULL)) {

    if ($music->insert($_POST['artist_id'],
                       $_POST['artist_name'],
                       $_POST['album_name'],
                       $music->formatDateTime($_POST['album_day'], $_POST['album_month'], $_POST['album_year']),
                       $_POST['artist_url'],
                       $_POST['picture_url'],
                       $_POST['store_url'],
		       $_POST['price'],
                       $_POST['download_id'],
                       $_POST['description']) ) {
        _e('The album was successfully entered into the database!', $i18n_domain);
    }
}

if ($_POST['show']) {
    $album_show = $_SESSION['album_show'] = true;
} else {
    $album_show = $_SESSION['album_show'] = false;

    echo '<center><form method="post" action=""><input type="submit" value="';
    _e('Create New Album', $i18n_domain);
    echo '" name="show" /></form></center><br/>';
}

echo "<div style='visibility:" .((!$album_show) ? "hidden" : "show"). ";" .((!$album_show) ? "height:0;" : ""). "'>";
    $music->display_manage_music_form();
echo "</div>";

echo "<div class='aform'><div id='dialog-form' title='" .__('Create New Album', $i18n_domain). "' style='display:none;'>\n"
   . "	<p class='validateTips'>" .__("All form fields are required.", $i18ndomain). "</p>\n"
   . "	<form>\n"
   . "	<fieldset>\n"
   . "		<label for='name'>Name</label>\n"
   . "		<input type='text' name='name' id='name' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>" .__("Birthday", $i18ndomain). "</label>\n"
   . "		<input type='text' name='birthday' id='birthday' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>" .__("Picture URL", $i18ndomain). "</label>\n"
   . "		<input type='text' name='picture_url' id='picture_url' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>" .__("Artist URL", $i18ndomain). "</label>\n"
   . "		<input type='text' name='artist_url' id='artist_url' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>" .__("Description", $i18ndomain). "</label>\n"
   . "		<input type='text' name='description' id='description' class='text ui-widget-content ui-corner-all' />\n"
   . "	</fieldset>\n"
   . "	</form>\n"
   . "</div>\n"
   . "<div id='music-contain' class='ui-widget'>\n"
   . "<button id='create-music'>" .__('Create New Album', $i18n_domain). "</button></div>\n"
   . "	<div style='float:left;'><h1>" .__('Existing Albums', $i18n_domain). ":</h1></div>\n"
   . "  <div style='float:right;border:1px dotted black; padding:10px;'>"
   . "    <label for='filter'>" .__('Filter:', $i18n_domain). "</label>"
   . "    <input type='text' name='filter' value='' id='filter' />"
   . "  </div>"
   . "	<table id='musicTable' class='ui-widget ui-widget-content'>\n"
   . "	    <thead>\n"
   . "	        <tr class='ui-widget-header '>\n"
   . "	            <th>" .__("ID", $i18n_domain). "</th>\n"
   . "	            <th>" .__("Art", $i18n_domain). "</th>\n"
   . "	            <th>" .__("Album", $i18n_domain). "</th>\n"
   . "		    <th>" .__("Downloads", $i18n_domain). "</th>\n"
   . "	            <th>" .__("Price", $i18n_domain). "</th>\n"
   . "	            <th>" .__("Actions", $i18n_domain). "</th>\n"
   . "	        </tr>\n"
   . "	    </thead>\n"
   . "      <tbody>\n";

if ($music->loadAll('id DESC')->getTotalRows() === 0) {
    echo '<tr><td colspan="7">';
    _e('No Albums Available in the Database!', $i18n_domain);
    echo '</td></tr>';
} else {
    for($i = 0; $i < $music->getTotalRows(); $i++) {
        $music->loadByNode($i);
        echo "<tr>
         <td>" .stripslashes($music->id). "</td>
         <td>
            <center>\n";
        echo "<a href='/download/$music->download_id' target='_blank'><img src='"
           . $music->picture_url. "' width='75' height='75' /></a>
         </td>
         <td>
              <a href='" .stripslashes($music->artist_url). "'>" .stripslashes($music->artist_name). "</a><br/>
              <a href='" .stripslashes($music->store_url). "'>" .stripslashes($music->album_name). "</a><br/>
          Released: <a href='" .stripslashes($store_url). "'>";
        echo $music->album_month. '.' .$music->album_day. '.' .$music->album_year. "
            </center>
         </td>";
	echo "<td>$music->total_downloads</td>\n";
        echo "<td>" .CURRENCY.$music->price. "</td>\n
          <td>";

         /* Edit Button */
        echo '<div style="float:left;"><form method="post" action=""><input type="hidden" value="'
           . stripslashes($music->id). '" name="edit" /><input type="submit" value="';
        _e('Edit', $i18n_domain);
        echo '" name="do_edit" /></form></div>';

         /* Delete Button */
        echo '<div style="float:left;">'
           . "  <button class='delete_button' id='delete_$music->id'>" .__('Delete', $i18n_domain). "</button>"
           . '</div>';

        echo "</td>
        </tr>\n";
    }
}

echo "	    </tbody>\n"
   . "	</table>\n"
   . "</div>\n";

unset($music);

?>
