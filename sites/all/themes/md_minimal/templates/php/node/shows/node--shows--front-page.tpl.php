<header class="accordion-header <?php print $classes; ?>" <?php print $attributes; ?>>

    <h3 class="decolumn_mini">
        <a class="dark-gray" <?php print $title_attributes; ?>><?php print $title; ?></a>
    </h3>

    <?php 

    if($node_url !== $uri_path) { ?>

    <div class="actions-links fsmall">
        <span class="action-link">
            <a class="action-link-view btn btn-success" href="<?php echo $node_url; ?>">View Show</a>
        </span>
    </div>

    <?php } ?>

    <span class="bootstrap_title toggle-image absolute"><?php echo (DannysComedyClub::$statusArray[$show_instance->getShowStatus()] != 'closed') ? 'Hide' : 'Show'; ?></span>

</header>