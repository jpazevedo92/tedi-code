<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Device extends Model
{
    public function network()
    {
        return $this->belongsTo(Network::class);
    }
}

