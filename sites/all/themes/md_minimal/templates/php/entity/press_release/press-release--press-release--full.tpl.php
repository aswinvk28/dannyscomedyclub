<article class="<?php print $classes; ?>" <?php print $attributes; ?> itemscope itemtype="http://schema.org/Review" itemprop="review">
    
    <div class="clearfix column">
        <span class="white">Title:</span>
        <meta itemprop="name" value="<?php print $press_release['name']; ?>" />
        <meta itemprop="url" value="<?php print $url; ?>" />
        <div class="clearfix column_small">
        <?php print theme('list_item_view', array(
            'ul_class' => 'act-tags',
            'li_class' => 'act-tag pull-left white',
            'items' => array(
                array(
                    'content' => '<a class="underline" href="'.$url.'">'.$press_release['name'].'</a>'
                )
            )
        )); ?>
        </div>
    </div>
    
    <div class="clearfix column">
        <span class="white">Press Release For:</span>
        <div itemprop="itemReviewed" itemscope itemtype="http://schema.org/Thing">
            <meta itemprop="url" value="<?php print $press_release['reference_path']; ?>" />
            <meta itemprop="name" value="<?php print $press_release['reference_title']; ?>" />
        </div>
        <div class="clearfix column_small">
        <?php print theme('list_item_view', array(
            'ul_class' => 'act-tags',
            'li_class' => 'act-tag pull-left white',
            'items' => array(
                array(
                    'content' => '<a class="underline" href="'.$press_release['reference_path'].'">'.$press_release['reference_title'].'</a>'
                )
            )
        )); ?>
        </div>
    </div>
    
    <?php if(!empty($press_release['author'])) { ?>
    <div class="clearfix column">
        <span class="white">Press Release Author:</span>
        <div class="clearfix column_small">
            <span><?php print $press_release['author']; ?></span>
        </div>
    </div>
    <?php } ?>
    
    <?php if(!empty($press_release['date'])) { ?>
    <div class="clearfix column">
        <span class="white">Press release Date:</span>
        <div class="clearfix column_small">
            <span><?php print $press_release['date']; ?></span>
        </div>
    </div>
    <?php } ?>
    
    <div class="clearfix column">
        <span class="white">Press Release:</span>
        <div class="clearfix column_small white">
        <?php print $press_release['description']; ?>
        </div>
    </div>
    
</article>