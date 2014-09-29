<article class="<?php echo $classes; ?>" <?php echo $attributes; ?> itemscope itemtype="http://schema.org/"<?php print $itemType; ?>>
    <meta itemprop="url" content="<?php echo $url; ?>" />
    <h3 class="clearfix" itemprop="performer" itemscope itemtype="http://schema.org/Person">
        <span><a class="underline pull-left heading_title" itemprop="url" href="<?php print $performer['path']; ?>"><span itemprop="name"><?php echo $performer['title']; ?></span></a></span>
        <span class="pull-right"><a class="btn btn-danger" href="<?php echo $url; ?>"> View Performance</a></span>
    </h3>
    <div class="clearfix decolumn_mini"><?php if(!empty($performer_tags)) { ?><span class="pull-left">&nbsp;&nbsp;<span class="badge"><?php echo $performer_tags; ?></span></span><?php } ?></div>
    <div class="row-fluid">
        <div class="span10">

            <div class="clearfix" itemprop="description"><?php print $description; ?></div>

            <?php
            print render($performer_press_quotes);
            print render($performance_press_quotes);
            ?>

        </div>
        <aside class="span2" itemprop="performer" itemscope itemtype="http://schema.org/Person">
            <?php print render($performer_image); ?>
        </aside>
    </div>
</article>