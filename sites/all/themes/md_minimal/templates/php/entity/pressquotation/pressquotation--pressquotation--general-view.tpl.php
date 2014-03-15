<div class="<?php print $classes; ?>" <?php print $attributes; ?>>

    <blockquote class="column_small press_quotes">
        <?php print $quote_body;
        if(!empty($agency)) { ?>
        <p class="clearfix column_mini large"><strong <?php print $title_attributes; ?>><?php print $agency; ?></strong></p>
        <?php } if(!empty($author)) { ?>
        <p class="clearfix column_mini large"><strong <?php print $title_attributes; ?>><?php print $author; ?></strong></p>
        <?php } ?>
    </blockquote>

</div>