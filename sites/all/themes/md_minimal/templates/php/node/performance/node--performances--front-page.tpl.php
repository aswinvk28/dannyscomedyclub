<article class="<?php echo $classes; ?>" <?php echo $attributes; ?>>

    <h3 class="clearfix decolumn_mini" <?php print $title_attributes; ?>>
        <span class="pull-left heading_title"><span><?php echo node_page_title($performer->getNode()); ?></span></span>
        <?php if(!empty($print_tags)) { ?><span class="pull-left">&nbsp;&nbsp;<span class="badge"><?php echo $print_tags; ?></span></span><?php } ?>
        <?php if(isset($performer_path)) { ?>
        <span class="pull-right"><a class="show-status-message"href="<?php echo $performer_path; ?>"> View Performer</a></span>
        <?php } ?>
    </h3>
    <div class="row-fluid">
        <div class="span10">

            <div class="clearfix"><?php print $description; ?></div>

            <?php
            print render($performer_press_quotes);
            print render($performance_press_quotes);
            ?>

        </div>
        <aside class="span2">
            <?php print $performer_image; ?>
        </aside>
    </div>

</article>