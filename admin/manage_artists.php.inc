<?php
$artist = new Artist;

if (strcmp($_POST['update'], NULL)) {
    if ($artist->updateById($_POST['artist_id'],
                            $_POST['artist_name'],
                            $_POST['url'],
                            $_POST['picture_url'],
                            $_POST['myspace_url'],
                            $artist->formatDateTime($_POST['artist_day'], $_POST['artist_month'], $_POST['artist_year']),
                            $_POST['artist_descr'],
                            (strcmp($_POST['enabled'], NULL)) ? TRUE : FALSE)) {
        _e("The artist was successfully updated in the database!<br/>\n", $i18n_domain);
    } else {
        _e("A problem occurred while trying to update the artist and the update information was lost!<br/>\n", $i18n_domain);
    }
}
else if (strcmp($_POST['edit'], NULL) && strcmp($_POST['edit'], '0')) {

    if (!strcmp($_POST['update'], NULL)) {

        if($artist->loadById($_POST['edit'])->getTotalRows() > 0) {
            $day = 0; $month = 0; $year = 0;
            $artist-> display_manage_artist_form ($artist->id, stripslashes($artist->name),
                                                  $day, $month, $year,
                                                  stripslashes($artist->picture_url),
                                                  stripslashes($artist->url),
                                                  stripslashes($artist->myspace_url),
                                                  stripslashes($artist->description),
                                                  $artist->enabled,
                                                  FALSE);
        }
    }
} else if (strcmp($_POST['new'], NULL) && strcmp($_POST['artist_name'], NULL)) {

    if ($artist->insert($_POST['artist_name'],
                        $_POST['url'],
                        $_POST['picture_url'],
                        $_POST['myspace_url'],
                        $artist->formatDateTime($_POST['artist_day'], $_POST['artist_month'], $_POST['artist_year']),
                        $_POST['artist_descr'],
                        (strcmp($_POST['enabled'], NULL)) ? TRUE : FALSE)) {
        _e('The artist was successfully entered into the database!', $i18n_domain);
    }
}

if ($_POST['show']) {
    $artist_show = $_SESSION['artist_show'] = TRUE;
} else {
    $artist_show = $_SESSION['artist_show'] = FALSE;

    echo '<center><form method="post" action=""><input type="submit" value="';
    _e('Create New Artist', $i18n_domain);
    echo '" name="show" /></form></center><br/>';
}

echo "<div style='visibility:" .((!$artist_show) ? "hidden" : "show"). ";" .((!$artist_show) ? "height:0;" : ""). "'>";
    $artist->display_manage_artist_form();
echo "</div>";

echo "<div class='aform'><div id='dialog-form' title='Create new Artist' style='display:none;'>\n"
   . "	<p class='validateTips'>All form fields are required.</p>\n"
   . "	<form>\n"
   . "	<fieldset>\n"
   . "		<label for='name'>Name</label>\n"
   . "		<input type='text' name='name' id='name' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>Birthday</label>\n"
   . "		<input type='text' name='birthday' id='birthday' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>Picture URL</label>\n"
   . "		<input type='text' name='picture_url' id='picture_url' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>Artist URL</label>\n"
   . "		<input type='text' name='artist_url' id='artist_url' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>MySpace URL</label>\n"
   . "		<input type='text' name='myspace_url' id='myspace_url' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>Enabled</label>\n"
   . "		<input type='checkbox' name='enabled' id='enabled' class='text ui-widget-content ui-corner-all' />\n"
   . "		<label for='name'>Description</label>\n"
   . "		<input type='text' name='description' id='description' class='text ui-widget-content ui-corner-all' />\n"
   . "	</fieldset>\n"
   . "	</form>\n"
   . "</div>\n"
   . "  <button id='create-artist'>" .__('Create New Artist', $i18n_domain). "</button></div>\n"
   . "	<div style='float:left;'><h1>" .__('Existing Artists:', $i18n_domain). "</h1></div>\n"
   . "  <div style='float:right;border:1px dotted black; padding:10px;'>"
   . "    <label for='filter'>" .__('Filter:', $i18n_domain). "</label>"
   . "    <input type='text' name='filter' value='' id='filter' /></div>"
   . "	<table id='artistsTable' class='ui-widget ui-widget-content'>\n"
   . "	    <thead>\n"
   . "	        <tr class='ui-widget-header '>\n"
   . "	            <th>ID</th>\n"
   . "	            <th>Art</th>\n"
   . "	            <th>Artist</th>\n"
   . "	            <th>Enabled</th>\n"
   . "	            <th>Actions</th>\n"
   . "	        </tr>\n"
   . "	    </thead>\n"
   . "      <tbody>\n";

if ($artist->loadAll('name ASC')->getTotalRows() === 0) {
  echo "	        <tr>\n"
     . "	            <td colspan='4'>\n"
     . __('No Artists Available in the Database!', $i18n_domain)
     . "\n	            </td>\n"
     . "	        </tr>\n";
} else {

    for($i = 0; $i < $artist->getTotalRows(); $i++) {
        $artist->loadByNode($i);

        echo "	        <tr>\n"
           . "	            <td>" .$artist->id. "</td>\n"
           . "	            <td>\n"
           . "<a href='" .stripslashes($artist->url)
           . "'><img width='75' height='75' src='" .stripslashes($artist->picture_url). "' /></a>"
           . "              </td><td>\n"
           . "                  <a href='" .stripslashes($artist->url). "'>" .stripslashes($artist->name). "</a>"
           . "              </td><td>\n"
           . (($artist->enabled) ? "<font color='green'>YES</font>" : "<font color='red'>NO</font>")
           . "              </td><td>\n"
           . '<div style="float:left"><form method="post" action=""><input type="hidden" value="'
           .   stripslashes($artist->id). '" name="edit" /><input type="submit" value="'
           . __('Edit', $i18n_domain)
           . '" name="do_edit" /></form></div>'
           . '<div style="float:left"><form method="post" action=""><input type="hidden" value="'
           .   stripslashes($artist->id) . '" name="edit" /><input type="submit" value="'
           . __('Toggle Enabled', $i18n_domain)
           . '" name="do_toggle_enabled" /></form></div>';

         /* Delete Button */
        echo '<div style="float:left;">'
           . "  <button class='delete_button' id='delete_$artist->id'>" .__('Delete', $i18n_domain). "</button>"
           . '</div>'
           . "              </td>\n"
           . "	        </tr>\n";
    }
}

echo "	    </tbody>\n"
   . "	</table>\n"
   . "</div>\n";

unset($artist);

?>