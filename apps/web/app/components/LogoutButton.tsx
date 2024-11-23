import { LogOutIcon } from "lucide-react";
import { getSession } from "../session";
import { LoaderFunction } from "@remix-run/node";
import { useLoaderData } from "@remix-run/react";

export const loader: LoaderFunction = async ({ request }) => {
    const session = await getSession(request.headers.get("Cookie"));
    const username = session.get("username");

    return { username };
};

export const LogoutButton = () => {

    const { username } = useLoaderData<typeof loader>();

    if (!username) return null;

    return (<a
        className="flex flex-row gap-2 text-sm font-medium px-4 py-2 hover:underline"
        href="/logout">
        <LogOutIcon height={20}
        />  Logout
    </a>
    );
}
