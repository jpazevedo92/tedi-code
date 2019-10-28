<table style="width:100%">
        <thead>
            <tr>
                <th>Interface Name</th>
                <th>Network Adress</th>
                <th>Operations</th>
            </tr>
        </thead>
        <tbody>
        @foreach($networks as $network)

            <tr>
                <td>{{$network->if_name}}</a></td> 
                <td>{{$network->network_address == NULL ? $network->tunnel_ip_out : $network->network_address}}</td>
                <td>
                    <div class="form-group">
                        <form action="{{'/networks/'.$network->id }}" method="post">
                            {{ csrf_field() }}
                            {{method_field('DELETE')}}
                            <a href="{{'/networks/'.$network->id.'/edit' }}" class="btn btn-warning"><i class="fa fa-edit"></i></a>
                            <button type="submit" class="btn btn-danger btn-xl">
                            <i class="fa fa-trash"></i>
                            </button>
                        </form>
                    </div>
            </td>
            </tr>
        @endforeach
        </tbody>
    </table>